cmake_minimum_required(VERSION 3.1)

############## C & CXX Flags ##############
IF(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
set(CMAKE_C_FLAGS       "-W3 /EHsc")
set(CMAKE_CXX_FLAGS     "-W3 /EHsc")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
ELSE()
set(CMAKE_C_FLAGS       "-Wall")
set(CMAKE_CXX_FLAGS     "-Wall")
ENDIF(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
set(CMAKE_C_STANDARD    11)
set(CMAKE_CXX_STANDARD  17)

############## Project name ##############
project(LumiEngine)

############## Options ##############
option(USE_ISPC "Use Intel Implicit SPMD (single program multiple data) Program Compiler (ISPC) in math library" ON)

############## Include directories ##############
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/thirdparty")

############## Target architecture detect ##############
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

############## Sources ##############
add_subdirectory(src)
add_subdirectory(thirdparty)

############## Test ##############
enable_testing()
add_subdirectory(test)