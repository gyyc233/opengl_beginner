#include "gl_window.h"
#include "material.h"
#include "mesh.h"
#include "shader.h"
#include <iostream>
#include <vector>

int main() {

  GL_Window gl_window(800, 480, std::string("draw the texture"));
  if (!gl_window.initialization()) {
    return -1;
  }

  Mesh *mesh = new Mesh();
  Material *material = new Material("../textures/img/img_test.png");
  Shader ourShader("../textures/shaders/vertex.txt",
                   "../textures/shaders/fragment.txt");

  while (!gl_window.checkClose()) {
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT);
    ourShader.Use();
    material->use();
    mesh->draw();

    gl_window.swapBuffer();
  }

  delete material;
  delete mesh;
  glfwTerminate();
  return 0;
}
