#include "gl_window.h"

GL_Window::GL_Window(int width, int height, std::string title)
    : width_(width), height_(height), title_(title) {
  initialization_ = false;
}

GL_Window::~GL_Window() { glfwTerminate(); }

bool GL_Window::initialization() {

  if (!glfwInit()) {
    std::cout << "failed to glfwInit" << std::endl;
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

  window_ = glfwCreateWindow(width_, height_, title_.c_str(), NULL, NULL);
  glfwMakeContextCurrent(window_);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    glfwTerminate();
    return false;
  }

  // Set up OpenGL
  glClearColor(0.25f, 0.5f, 0.75f, 1.0f);
  // Set the rendering region to the actual screen size
  int w, h;
  glfwGetFramebufferSize(window_, &w, &h);
  //(left, top, width, height)
  glViewport(0, 0, w, h);

  initialization_ = true;
  std::cout << "GL_Window success to initialization" << std::endl;
  return true;
}

GLFWwindow *GL_Window::getHandle() {
  if (!initialization_) {
    std::cout << "GL_Window failed to initialization" << std::endl;
    return nullptr;
  }

  return window_;
}

int GL_Window::checkClose() { return glfwWindowShouldClose(this->window_); }

void GL_Window::swapBuffer() { glfwSwapBuffers(this->window_); }
