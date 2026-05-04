# Sandbox：executable application, link Sword
cmake_minimum_required(VERSION 3.16)
project(Sandbox LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SANDBOX_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

# generate executable application
add_executable(Sandbox ${SANDBOX_SOURCES})

# add_subdirectory(${PROJECT_SOURCE_DIR}/../Sword/src)

# Link against Sword and other static libraries
target_link_libraries(Sandbox
    PRIVATE
        Sword
        opengl32
        gdi32
)

# GLFW setup for Sandbox (since Sword is static now)
set(GLFW_ROOT ${CMAKE_SOURCE_DIR}/vendor/glfw-3.4.bin.WIN64)
target_include_directories(Sandbox PRIVATE ${GLFW_ROOT}/include)
target_link_directories(Sandbox PRIVATE ${GLFW_ROOT}/lib-mingw-w64)
target_link_libraries(Sandbox PRIVATE
    ${GLFW_ROOT}/lib-mingw-w64/libglfw3dll.a
)

set_target_properties(Sandbox PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../bin"
)