# Sword：生成 DLL 动态库
cmake_minimum_required(VERSION 3.16)
project(Sword LANGUAGES CXX)

# C++ 标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 【核心】生成 SHARED 动态库（Windows = DLL）
add_library(Sword SHARED
    Sword.h
)

# 定义导出宏（自动生效，无需手动写）
target_compile_definitions(Sword PRIVATE SW_PLATFORM_WINDOWS SW_BUILD_DLL)

# 公开头文件目录（Sandbox 可直接引用）
target_include_directories(Sword
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Windows 优化：去掉 lib 前缀
set_target_properties(Sword PROPERTIES PREFIX "")
