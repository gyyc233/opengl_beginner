#ifndef MESH_H
#define MESH_H
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
// clang-format on
#include <iostream>
#include <vector>

class Mesh {
public:
  Mesh();
  void draw();
  ~Mesh();

private:
  unsigned int EBO, VAO, element_count;
  std::vector<unsigned int> VBOs;
};

#endif