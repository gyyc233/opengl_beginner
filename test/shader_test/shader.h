#ifndef SHADER_H
#define SHADER_H
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
// clang-format on

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
public:
  Shader() = delete;
  ~Shader();
  GLuint Program;
  // Constructor generates the shader on the fly
  Shader(const GLchar *vertexPath, const GLchar *fragmentPath);
  // Uses the current shader
  void Use();
};

#endif
