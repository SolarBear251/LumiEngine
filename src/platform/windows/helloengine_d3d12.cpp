/**
 * @file       helloengine_d3d12.cpp
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-09
 * 
 * @brief    Hello world for D3D12
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#include <windows.h>
#include <windowsx.h>

#include <d3d12.h>
#include "d3dx12.h"
#include <dxgi1_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>

#include <wrl/client.h>

#include <tchar.h>
#include <cstdint>
#include <string>
#include <exception>
#include <iostream>

using namespace DirectX;
using namespace DirectX::PackedVector;
using namespace Microsoft::WRL;

constexpr uint32_t ScreenWidth = 960;
constexpr uint32_t ScreenHeight = 480;
constexpr uint32_t FrameCnt = 2;
constexpr bool UseWarpDevice = true;

// Global declarations
D3D12_VIEWPORT                      gViewPort    = {0, 0, ScreenWidth, ScreenHeight}; ///< Viewport
D3D12_RECT                          gScissorRect = {0, 0, ScreenWidth, ScreenHeight}; ///< Scissor rect
ComPtr<IDXGISwapChain3>             gSwapChain   = nullptr; ///< Pointer to the swap chain interface
ComPtr<ID3D12Device>                gDev         = nullptr; ///< Pointer to our Direct3D device interface
ComPtr<ID3D12Resource>              gRendenTargets[FrameCnt]; ///< Pointer to rendering buffer[descriptor]
ComPtr<ID3D12CommandAllocator>      gCommandAllocator; ///< Pointer to command buffer allocator
ComPtr<ID3D12CommandQueue>          gCommandQueue; ///< Pointer to command queue
ComPtr<ID3D12RootSignature>         gRootSignature; ///< A graphics root signature defines what resources are bound to the pipeline
ComPtr<ID3D12DescriptorHeap>        gRtvHeap; ///< An array of descriptors of GPU objects
///< An object maintains the state of all currently set shaders and certain
///< fixed funtion state objects, such as the input assembler, tesselator,
///< rasterizer and output manager
ComPtr<ID3D12PipelineState>         gPipelineState; 
ComPtr<ID3D12GraphicsCommandList>   gCommandList; ///< A list to store GPU commands which will be submitted to GPU to execute when done
uint32_t                            gRtvDescriptorSize; ///< Size of Rtv descriptor
ComPtr<ID3D12Resource>              gVertexBuffer; ///< Pointer to the vertex buffer
D3D12_VERTEX_BUFFER_VIEW            gVertexBufferView; ///< A view of the vertex buffer

/// Synchonization objects
uint32_t                            gFrameIndex;
HANDLE                              gFenceEvent;
ComPtr<ID3D12Fence>                 gFence;
uint32_t                            gFenceValue;


std::wstring                        gAssetsPath;

// Vertex buffer structure
struct VERTEX {
    XMFLOAT3 Position;
    XMFLOAT4 Color;
};

// Helper class for COM exceptions
class ComException : public std::exception {
private:
    HRESULT result;
public:
    ComException(HRESULT hr) : result(hr) {}
    virtual const char* what() const override {
        static char s_str[64] = {0};
        sprintf_s(s_str, "Failure with HRESULT of %08X", static_cast<unsigned int>(result));

        return s_str;
    }
};

/**
 * @brief Helper function converts D3D API failures into exceptions
 *
 */
inline void ThrowIfFailed(HRESULT hr) {
    if(FAILED(hr)) {
        throw ComException(hr);
    }
}

/**
 * @brief    Helper function for resolving the full path of assets
 *
 */
std::wstring GetAssetFullPath(LPCWSTR assetName) {
    return gAssetsPath + assetName;
}

/**
 * @brief    Get assets path
 *
 */
void GetAssetsPath(WCHAR* path, UINT pathSize) {
    if(!path) {
        throw std::exception();
    }
    DWORD size = GetModuleFileNameW(nullptr, path, pathSize);
    if (size == 0 || size == pathSize) {
        throw std::exception();
    }
    WCHAR* lastSlash = wcsrchr(path, L'\\');
    if (lastSlash) {
        *(lastSlash + 1) = L'\0';
    }
}

/**
 * @brief    Waiting for the frame to complete before continuing is not best practice. This is code implemented as such for simplicity.
 * More advanced samples illustrate how to use fences for efficient resource usage
 * 
 */
void WaitForPreviousFrame() {
    // Signal and increment the fence value
    const uint64_t fence = gFenceValue;
    ThrowIfFailed(gCommandQueue->Signal(gFence.Get(), fence));
    ++gFenceValue;

    // Wait until the previous frame is finished
    if (gFence->GetCompletedValue() < fence) {
        ThrowIfFailed(gFence->SetEventOnCompletion(fence, gFenceEvent));
        WaitForSingleObject(gFenceEvent, INFINITE);
    }
    gFrameIndex = gSwapChain->GetCurrentBackBufferIndex();
}

/**
 * @brief    Create Render Target
 * 
 */
void CreateRenderTarget() {
    // Describe and create a render target view (RTV) descriptor heap
    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
    rtvHeapDesc.NumDescriptors = FrameCnt;
    rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    ThrowIfFailed(gDev->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&gRtvHeap)));

    gRtvDescriptorSize = gDev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(gRtvHeap->GetCPUDescriptorHandleForHeapStart());

    // Create a RTV for each frame
    for (uint32_t i = 0; i < FrameCnt; ++i) {
        ThrowIfFailed(gSwapChain->GetBuffer(i, IID_PPV_ARGS(&gRendenTargets[i])));
        gDev->CreateRenderTargetView(gRendenTargets[i].Get(), nullptr, rtvHandle);
        rtvHandle.Offset(1, gRtvDescriptorSize);
    }
}

/**
 * @brief    Loads and prepares the shaders
 * 
 */
void InitPipeline() {
    ThrowIfFailed(gDev->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&gCommandAllocator)));

    // Create an empty root signature
    CD3DX12_ROOT_SIGNATURE_DESC rsd;
    rsd.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    ComPtr<ID3DBlob> signature;
    ComPtr<ID3DBlob> error;
    ThrowIfFailed(D3D12SerializeRootSignature(&rsd, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
    ThrowIfFailed(gDev->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&gRootSignature)));

    // load the shaders
#ifdef _DEBUG
    // Enable better shader debugging with the graphics debugging tools
    UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
    UINT compileFlags = 0;
#endif
    ComPtr<ID3DBlob> vertexShader;
    ComPtr<ID3DBlob> pixelShader;
    // Vertex shader
    D3DCompileFromFile(
        GetAssetFullPath(L"copy.vs").c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main",
        "vs_5_0",
        compileFlags,
        0,
        &vertexShader,
        &error
    );
    if (error) {
        OutputDebugString((LPCTSTR)error->GetBufferPointer());
        error->Release();
        throw std::exception();
    }
    // Pixel shader
    D3DCompileFromFile(
        GetAssetFullPath(L"copy.ps").c_str(),
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main",
        "ps_5_0",
        compileFlags,
        0,
        &pixelShader,
        &error
    );
    if (error) {
        OutputDebugString((LPCTSTR)error->GetBufferPointer());
        error->Release();
        throw std::exception();
    }

    // Create the input layout object
    D3D12_INPUT_ELEMENT_DESC ied[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
    };

    // Describe and create the graphics pipeline state object (PSO)
    D3D12_GRAPHICS_PIPELINE_STATE_DESC psod = {};
    psod.InputLayout = {ied, _countof(ied)};
    psod.pRootSignature = gRootSignature.Get();
    psod.VS = {reinterpret_cast<UINT8*>(vertexShader->GetBufferPointer()), vertexShader->GetBufferSize()};
    psod.PS = {reinterpret_cast<UINT8*>(pixelShader->GetBufferPointer()), pixelShader->GetBufferSize()};
    psod.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    psod.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    psod.DepthStencilState.DepthEnable = FALSE;
    psod.DepthStencilState.StencilEnable = FALSE;
    psod.SampleMask = UINT_MAX;
    psod.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psod.NumRenderTargets = 1;
    psod.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    psod.SampleDesc.Count = 1;

    ThrowIfFailed(gDev->CreateGraphicsPipelineState(&psod, IID_PPV_ARGS(&gPipelineState)));
    ThrowIfFailed(gDev->CreateCommandList(0,
     D3D12_COMMAND_LIST_TYPE_DIRECT, 
     gCommandAllocator.Get(), 
     gPipelineState.Get(), 
     IID_PPV_ARGS(&gCommandList)));
    ThrowIfFailed(gCommandList->Close());
}

/**
 * @brief    Creates the shape to render
 * 
 */
void InitGraphics() {
    // Create a triangle using the VERTEX struct
    VERTEX vertices[] = {
        {XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
        {XMFLOAT3(0.45f, -0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
        {XMFLOAT3(-0.45f, -0.5f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)},
    };
    const UINT vertexBufferSize = sizeof(vertices);

    // Note: using upload heaps to transfer static data like vert buffers is not
    // recommended. Every time the GPU needs it, the upload heap will be
    // marshalled over. Please read up on Default Heap usage. An upload heap is
    // used here for code simplicity and because there are very few verts to
    // actually transfer.
    ThrowIfFailed(gDev->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
        D3D12_HEAP_FLAG_NONE,
        &CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize),
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&gVertexBuffer)
    ));
    // Copy the vertices into the buffer
    uint8_t* vertexDataBegin;
    CD3DX12_RANGE readRange(0, 0); ///< We do not intend to read the buffer on CPU
    ThrowIfFailed(gVertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&vertexDataBegin))); ///< Map the buffer
    memcpy(vertexDataBegin, vertices, vertexBufferSize); ///< Copy the data
    gVertexBuffer->Unmap(0, nullptr); ///< Unmap the buffer

    // Init the vertex buffer view
    gVertexBufferView.BufferLocation = gVertexBuffer->GetGPUVirtualAddress();
    gVertexBufferView.StrideInBytes = sizeof(VERTEX);
    gVertexBufferView.SizeInBytes = vertexBufferSize;

    // Create synchronization objects and wait until assets have been uploaded to GPU
    ThrowIfFailed(gDev->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&gFence)));
    gFenceValue = 1;
    // Create event handle for frame synchronization
    gFenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    if (gFenceEvent == nullptr) {
        ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
    }

    // Wait for the command list to execute; we are reusing the same command
    // in out main loop, but for now, we just want to wait for setup to complete before continuing
    WaitForPreviousFrame();
}

/**
 * @brief    Get hardware adapter
 * 
 */
void GetHardwareAdapter(IDXGIFactory4* pFactory, IDXGIAdapter1** ppAdapter) {
    IDXGIAdapter1* pAdapter = nullptr;
    *ppAdapter = nullptr;

    for (UINT adapterIndex = 0; pFactory->EnumAdapters1(adapterIndex, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++adapterIndex) {
        DXGI_ADAPTER_DESC1 desc;
        pAdapter->GetDesc1(&desc);
        if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
            // Don't select the basic render driver adapter
            continue;
        }
        // Check to see if the adapter supports D3D12,
        // But don't create the actual device yet
        if (SUCCEEDED(D3D12CreateDevice(pAdapter, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr))) {
            break;
        }        
    }

    *ppAdapter = pAdapter;
}

/**
 * @brief    A Summary function to prepare graphic resources
 * 
 */
void CreateGraphicsResources(HWND hWnd) {
    if (!gSwapChain) {
#ifdef _DEBUG
        // Enable D3D12 debug layer
        {
            ComPtr<ID3D12Debug> debugController;
            if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
                debugController->EnableDebugLayer();
            }
        }
#endif
        // Create device
        ComPtr<IDXGIFactory4> factory;
        ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&factory)));
        if (UseWarpDevice) {
            ComPtr<IDXGIAdapter> warpAdapter;
            ThrowIfFailed(factory->EnumWarpAdapter(IID_PPV_ARGS(&warpAdapter)));

            ThrowIfFailed(D3D12CreateDevice(warpAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&gDev)));
        } else {
            ComPtr<IDXGIAdapter1> hardwareAdapter;
            GetHardwareAdapter(factory.Get(), &hardwareAdapter);

            ThrowIfFailed(D3D12CreateDevice(hardwareAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&gDev)));
        }

        // Describe and create the command queue
        D3D12_COMMAND_QUEUE_DESC queueDesc = {};
        queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        queueDesc.Type  = D3D12_COMMAND_LIST_TYPE_DIRECT;

        ThrowIfFailed(gDev->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&gCommandQueue)));

        // Create a struct to hold information about swap chain
        DXGI_SWAP_CHAIN_DESC scd;
        ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
        scd.BufferCount = FrameCnt; ///< back buffer count
        scd.BufferDesc.Width = ScreenWidth;
        scd.BufferDesc.Height = ScreenHeight;
        scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; ///< 32-bit color
        scd.BufferDesc.RefreshRate.Numerator = 60;
        scd.BufferDesc.RefreshRate.Denominator = 1;
        scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; ///< how swap chain is to be used
        scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; ///< This only supported after Win10, use DXGI_SWAP_EFFECT_DISCARD before Win10
        scd.OutputWindow = hWnd; ///< the window to be used
        scd.SampleDesc.Count = 1; ///< multi-samples cannot be used when in above SwaoEffect
        scd.Windowed = TRUE; ///< Windowed / full-screen
        scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; ///< allow full-screen transition

        ComPtr<IDXGISwapChain> swapChain;
        ThrowIfFailed(factory->CreateSwapChain(
            gCommandQueue.Get(), ///< Swap chain needs the queue so it can force a flush on it
            &scd,
            &swapChain
        ));
        ThrowIfFailed(swapChain.As(&gSwapChain));
        gFrameIndex = gSwapChain->GetCurrentBackBufferIndex();

        CreateRenderTarget();
        InitPipeline();
        InitGraphics();
    }
}

/**
 * @brief    Clear graphics resources
 * 
 */
void DiscardGraphicsResources() {
    WaitForPreviousFrame();
    CloseHandle(gFenceEvent);
}

/**
 * @brief    Populate Command List
 * 
 */
void PopulateCommandList() {
    // Command list allocators can only be reset when the associated
    // command lists have finished execution on the GPU; apps should use
    // fences to determine GPU execution progress.
    ThrowIfFailed(gCommandAllocator->Reset());

    // However, when ExecuteCommandList() is called on a particular command list, 
    // that command list can then be reset at any time and must be before re-recording.
    ThrowIfFailed(gCommandList->Reset(gCommandAllocator.Get(), gPipelineState.Get()));

    // Set necessary state
    gCommandList->SetGraphicsRootSignature(gRootSignature.Get());
    gCommandList->RSSetViewports(1, &gViewPort);
    gCommandList->RSSetScissorRects(1, &gScissorRect);

    // Indicate that the back buffer will be used as a render target
    gCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(
        gRendenTargets[gFrameIndex].Get(),
        D3D12_RESOURCE_STATE_PRESENT,
        D3D12_RESOURCE_STATE_RENDER_TARGET
    ));
    CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(gRtvHeap->GetCPUDescriptorHandleForHeapStart(), gFrameIndex, gRtvDescriptorSize);
    gCommandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

    // Clear the back buffer to a deep blue
    const FLOAT clearColor[] = {0.0f, 0.2f, 0.4f, 1.0f};
    gCommandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

    // Do 3D rendering on the back buffer
    {
        // Select which vertex buffer to display
        gCommandList->IASetVertexBuffers(0, 1, &gVertexBufferView);
        // Select which primitive type we are using
        gCommandList->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        // Draw the vertex buffer to the back buffer
        gCommandList->DrawInstanced(3, 1, 0, 0);
    }

    // Indicate that the back buffer will now be used to present
    gCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(
        gRendenTargets[gFrameIndex].Get(),
        D3D12_RESOURCE_STATE_RENDER_TARGET,
        D3D12_RESOURCE_STATE_PRESENT
    ));
    ThrowIfFailed(gCommandList->Close());

}

/**
 * @brief    Render a frame
 * 
 */
void RenderFrame() {
    // Record all the commands we need to render the scene into the command list
    PopulateCommandList();

    // Execute the command list
    ID3D12CommandList* commandLists[] = {
        gCommandList.Get(),
    };
    gCommandQueue->ExecuteCommandLists(_countof(commandLists), commandLists);

    // Swap the back buffer and the front buffer
    ThrowIfFailed(gSwapChain->Present(1, 0));

    WaitForPreviousFrame();
}

/**
 * @brief    WindowProc funtion
 * 
 */
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam,
                            LPARAM lParam) {
    LRESULT result = 0;
    bool wasHandled = false;

    // sort through and find what code to run for message given
    switch (message) {
        case WM_CREATE:
            wasHandled = true;
            break;
        case WM_PAINT:
            CreateGraphicsResources(hWnd);
            RenderFrame();
            wasHandled = true;
            break;
        case WM_SIZE:
            if (gSwapChain != nullptr) {
                DiscardGraphicsResources();
                gSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
            }
            wasHandled = true;
            break;
        case WM_DESTROY:
            DiscardGraphicsResources();
            PostQuitMessage(0);
            wasHandled = true;
            break;
        case WM_DISPLAYCHANGE:
            InvalidateRect(hWnd, nullptr, false);
            wasHandled = true;
            break;
    }
    if (!wasHandled) {
        result = DefWindowProc(hWnd, message, wParam, lParam);
    }
    return result;
}

/**
 * @brief    Entry of Windows program
 * 
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPTSTR lpCmdLine, int nCmdShow) {
    // Handle for the window
    HWND hWnd;
    // Info for the window class
    WNDCLASSEX wc;

    WCHAR assetsPath[512];
    GetAssetsPath(assetsPath, _countof(assetsPath));
    gAssetsPath = assetsPath;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    // fill in the info
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = _T("WindowClass1");

    // register the window class
    RegisterClassEx(&wc);
    // Create the window and use the result as the handle
    hWnd = CreateWindowEx(
        0,
        _T("WindowClass1"), ///< name of the window class
        _T("Hello, Engine! [D3D12]"), ///< title of the window
        WS_OVERLAPPEDWINDOW, ///< window style
        100, ///< x-position
        100, ///< y-position
        ScreenWidth, ///< width of the window
        ScreenHeight, ///< height of the window
        NULL, ///< parent window
        NULL, ///< menus
        hInstance, ///< application handle
        NULL ///< used with multiple windows
    );
    // Show the window
    ShowWindow(hWnd, nCmdShow);

    // Main loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        // Translate keystroke messages into right format
        TranslateMessage(&msg);
        // Send the message to WindowProc function
        DispatchMessage(&msg);
    }

    // return this part of the WM_QUIT message to Windows
    return msg.wParam;
}
