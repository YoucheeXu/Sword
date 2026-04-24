# ImGui CMake 配置 (静态库，适配 GLFW3 + OpenGL3 + GLAD)
cmake_minimum_required(VERSION 3.16)
project(imgui LANGUAGES CXX)

# 收集 ImGui 核心源码
file(GLOB IMGUI_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

# 收集 GLFW3 + OpenGL3 后端源码
file(GLOB IMGUI_BACKENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

# 创建 ImGui 静态库（静态链接，无DLL，最稳定）
add_library(imgui
    STATIC
        ${IMGUI_SOURCES}
        ${IMGUI_BACKENDS}
)

# 头文件路径（公开给外部项目使用）
target_include_directories(imgui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/backends
        ${CMAKE_SOURCE_DIR}/vendor/glfw-3.4.bin.WIN64/include
)

# 依赖：链接 GLFW + GLAD + OpenGL（自动继承）
target_link_libraries(imgui
    PUBLIC
        glad
        opengl32
)

# 核心宏：告诉 ImGui 使用 GLAD 加载 OpenGL
target_compile_definitions(imgui
    PUBLIC
        IMGUI_IMPL_OPENGL_LOADER_GLAD
        IMGUI_DISABLE_OBSOLETE_FUNCTIONS
)
