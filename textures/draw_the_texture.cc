#include "material.h"
#include "shader.h"
#include <iostream>

int main() {

  GLFWwindow *window;

  if (!glfwInit()) {
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  window = glfwCreateWindow(640, 480, "Draw the texture!", NULL, NULL);
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    glfwTerminate();
    return -1;
  }

  // Set up OpenGL
  glClearColor(0.25f, 0.5f, 0.75f, 1.0f);
  // Set the rendering region to the actual screen size
  int w, h;
  glfwGetFramebufferSize(window, &w, &h);
  //(left, top, width, height)
  glViewport(0, 0, w, h);

  // Build and compile our shader program
  Shader ourShader("../textures/shaders/vertex.txt",
                   "../textures/shaders/fragment.txt");
  Material *material = new Material("../textures/img/img_test.png");

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT);
    ourShader.Use();
    material->use();

    glfwSwapBuffers(window);
  }

  delete material;
  glfwTerminate();
  return 0;
}
