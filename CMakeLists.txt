cmake_minimum_required(VERSION 3.10)
project(opengl_beginner VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW) # use to find OpenGL

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_LIBRARIES "-lX11 -ldl") # fixed undefined reference to symbol 'dlclose@@GLIBC_2.2.5'

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
