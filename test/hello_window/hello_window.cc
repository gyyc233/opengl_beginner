#include "config.h"

int main() {

  GLFWwindow *window;

  if (!glfwInit()) {
    return -1;
  }

  window = glfwCreateWindow(640, 480, "Hello Window!", NULL, NULL);

  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Couldn't load opengl" << std::endl;
    glfwTerminate();
    return -1;
  }

  glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(1.0f, -0.5f);
    glEnd();

    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}
