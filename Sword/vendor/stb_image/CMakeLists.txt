# stb_image/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(stb_image LANGUAGES C)

# 编译 stb_image 为静态库（轻量无依赖）
add_library(stb_image STATIC stb_image.c)

# 设置头文件路径（给外部项目使用）
target_include_directories(stb_image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
