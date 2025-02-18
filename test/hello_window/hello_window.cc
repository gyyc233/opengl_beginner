#include "config.h"

#include <iostream>

int main() {
  // create a glfw window.
  GLFWwindow *window;

  if (!glfwInit()) {
    return -1;
  }

  // tell GLFW to make the window the current context
  window = glfwCreateWindow(640, 480, "Hello Window!", NULL, NULL);
  glfwMakeContextCurrent(window);

  // tell glad to load the gl loader, use glfw's
  //			GetProcAddress function
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Couldn't load opengl" << std::endl;
    glfwTerminate();
    return -1;
  }

  // tell OpenGL what rgba color we want to use for
  //		screen refresh.
  glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    // tell OpenGL to clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and events 轮寻和事件*/
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
