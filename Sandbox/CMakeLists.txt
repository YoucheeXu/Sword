# Sandbox：可执行程序，调用 Sword DLL
cmake_minimum_required(VERSION 3.16)
project(Sandbox LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SANDBOX_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

# 生成可执行文件
add_executable(Sandbox ${SANDBOX_SOURCES})

# add_subdirectory(${PROJECT_SOURCE_DIR}/../Sword/src)

# 【核心】链接 Sword 库（自动处理头文件 + DLL + 导入库）
target_link_libraries(Sandbox PRIVATE Sword)

set_target_properties(Sandbox PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../bin"
)