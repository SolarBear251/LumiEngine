/**
 * @file       D3D12GraphicsManager.h
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-09
 * 
 * @brief    Graphics Manager using D3D12 graphic interface
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#pragma once

// TODO: change D3d11 to D3d12


#include "core/GraphicsManager.h"

namespace Lumi {

class D3D12GraphicsManager : public GraphicsManager {
private:

public:
    D3D12GraphicsManager() = default;
    virtual ~D3D12GraphicsManager() = default;

    /// Override functions
    virtual int Initialize() override;
    virtual void Finalize() override;
    virtual void Render() override;

};  ///< class D3D12GraphicsManager

}; ///< namespace Lumi