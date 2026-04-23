# Sword：生成 DLL 动态库
cmake_minimum_required(VERSION 3.16)
project(Sword LANGUAGES CXX)

# C++ 标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ========================
# 🔥 全自动扫描所有 .cpp 源码（核心！）
# 递归查找 src/Sword/ 下 所有 .cpp 文件
# ========================
file(GLOB_RECURSE SWORD_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Sword/*.cpp
)

# 自动把所有扫描到的源码编译成 DLL
add_library(Sword SHARED ${SWORD_SOURCES})

# 定义导出宏（自动生效，无需手动写）
target_compile_definitions(Sword
    PUBLIC
        $<$<PLATFORM_ID:Windows>:SW_PLATFORM_WINDOWS>
        SW_BUILD_DLL
)

# 公开头文件目录（Sandbox 可直接引用）
target_include_directories(Sword
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
)

set_target_properties(Sword PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../bin"
)
