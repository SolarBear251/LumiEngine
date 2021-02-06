cmake_minimum_required(VERSION 3.1)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
project(LumiEngine)

include_directories("${PROJECT_SOURCE_DIR}/include")

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(TargetArchDetect)
target_architecture(TARGET_ARCH)

if((TARGET_ARCH MATCHES "x86_64" OR TARGET_ARCH MATCHES "ia64") AND NOT OF_32BIT)
    set(ARCH_BIT 64)
else()
    set(ARCH_BIT 32)
endif()

MESSAGE( STATUS "TARGET_ARCH: " ${TARGET_ARCH} )
MESSAGE( STATUS "ARCH_BIT: " ${ARCH_BIT} )

add_subdirectory(src)
add_subdirectory(thirdparty)

enable_testing()
add_subdirectory(test)