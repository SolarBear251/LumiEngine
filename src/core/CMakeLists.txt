set(LUMI_CORE_SOURCES
    Config.cpp
    AssetLoader.cpp
    Allocator.cpp
    MemoryManager.cpp
    BaseApplication.cpp
    GraphicsManager.cpp
    main.cpp
)

add_library(lumi_core
    ${LUMI_CORE_SOURCES}
    ${LUMI_CORE_HEADERS}
)
