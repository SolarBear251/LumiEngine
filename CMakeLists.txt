cmake_minimum_required(VERSION 3.1)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
project(LumiEngine)

include_directories("${PROJECT_SOURCE_DIR}/core/common")
include_directories("${PROJECT_SOURCE_DIR}/core/interface")

add_subdirectory(core)
add_subdirectory(empty)
