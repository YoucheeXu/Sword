# Sword：complie to static lib
cmake_minimum_required(VERSION 3.16)
project(Sword LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/imgui-1.92.7-docking)
add_subdirectory(vendor/glm-1.0.3)
add_subdirectory(vendor/stb_image)

# ========================
# Automatic recursive scan for all .cpp sources
# Locate all .cpp files recursively in the src/ directory
# ========================
file(GLOB_RECURSE SWORD_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

# add_library(Sword SHARED ${SWORD_SOURCES})
add_library(Sword STATIC ${SWORD_SOURCES}) # complie to static lib

# Compile definitions
target_compile_definitions(Sword
    PRIVATE
        GLFW_DLL
    PUBLIC
        $<$<PLATFORM_ID:Windows>:SW_PLATFORM_WINDOWS>
        SW_BUILD_DLL
        SW_DEBUG
)

# Include directories
target_include_directories(Sword
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog-1.17.0/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm-1.0.3
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui-1.92.7-docking
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image
)

# GLFW setup (PRIVATE for Sword only)
set(GLFW_ROOT ${CMAKE_SOURCE_DIR}/vendor/glfw-3.4.bin.WIN64)
target_include_directories(Sword PRIVATE ${GLFW_ROOT}/include)
target_link_directories(Sword PRIVATE ${GLFW_ROOT}/lib-mingw-w64)

target_link_libraries(Sword
    PRIVATE
        stb_image
        glm
        imgui
        glad
        libglfw3dll.a
        opengl32
        gdi32
)

add_custom_command(
    TARGET Sword POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${GLFW_ROOT}/lib-mingw-w64/glfw3.dll
        ${CMAKE_BINARY_DIR}/../bin/glfw3.dll
)

set_target_properties(Sword PROPERTIES

    # RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../bin" # Static lib output directory
)
