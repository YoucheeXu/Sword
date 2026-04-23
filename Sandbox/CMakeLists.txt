# Sandbox：可执行程序，调用 Sword DLL
cmake_minimum_required(VERSION 3.16)
project(Sandbox LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 生成可执行文件
add_executable(Sandbox src/SandboxApp.cpp)

# 【核心】链接 Sword 库（自动处理头文件 + DLL + 导入库）
target_link_libraries(Sandbox PRIVATE Sword)
