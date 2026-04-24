# glad/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(glad LANGUAGES C)

# 编译 GLAD 为静态库（轻量无依赖）
add_library(glad STATIC src/glad.c)

# 设置头文件路径（给外部项目使用）
target_include_directories(glad PUBLIC include)
