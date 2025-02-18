cmake_minimum_required(VERSION 3.10)
project(opengl_beginner VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW) # use to find OpenGL

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_LIBRARIES "-lX11 -ldl") # 

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