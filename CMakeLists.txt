cmake_minimum_required(VERSION 3.10)
project(opengl_beginner VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW) # use to find OpenGL

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_LIBRARIES "-lX11 -ldl") # fixed undefined reference to symbol 'dlclose@@GLIBC_2.2.5'

# set gdb debug or release 
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(hello_window
    test/hello_window/config.h
    test/hello_window/hello_window.cc
    test/hello_window/glad.c
)

target_include_directories(hello_window 
    PRIVATE
    dependencies 
)

target_link_libraries(hello_window
    glfw
    OpenGL::GL 
)

# what_are_shaders
add_executable(what_are_shaders
    test/what_are_shaders/config.h
    test/what_are_shaders/triangle_mesh.cc
    test/what_are_shaders/what_are_shaders.cc
    test/what_are_shaders/glad.c
)

target_include_directories(what_are_shaders 
    PRIVATE
    dependencies 
)

target_link_libraries(what_are_shaders
    glfw
    OpenGL::GL 
)

# triangle_test
add_executable(triangle_test
    test/triangle_test/triangle_test.cc
    test/triangle_test/glad.c
)

target_include_directories(triangle_test 
    PRIVATE
    dependencies 
)

target_link_libraries(triangle_test
    glfw
    OpenGL::GL 
)

# shader_test
add_executable(shader_test
    test/shader_test/shader_test.cc
    test/shader_test/shader.cc
    test/shader_test/glad.c
)

target_include_directories(shader_test 
    PRIVATE
    dependencies 
)

target_link_libraries(shader_test
    glfw
    OpenGL::GL 
)

# textures
# draw_the_texture
add_executable(draw_the_texture
    textures/draw_the_texture.cc
    textures/shader.cc
    textures/glad.c
    textures/material.cc
    textures/mesh.cc
    textures/gl_window.cc
)

target_include_directories(draw_the_texture 
    PRIVATE
    dependencies 
)

target_link_libraries(draw_the_texture
    glfw
    OpenGL::GL 
)
