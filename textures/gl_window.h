#ifndef GL_WINDOW_H
#define GL_WINDOW_H
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
// clang-format on
#include <iostream>
#include <string>

class GL_Window {
public:
  GL_Window() = delete;

  /// @brief GLFWwindow config
  /// @param width window width
  /// @param height window height
  /// @param title window title
  explicit GL_Window(int width, int height, std::string title);

  ~GL_Window();

  /// @brief initialize GLAD and window
  /// @return
  bool initialization();

  /// @brief get GLFWwindow handle
  /// @return
  GLFWwindow *getHandle();

  int checkClose();

  void swapBuffer();

private:
  GLFWwindow *window_;
  int width_;
  int height_;
  std::string title_;
  bool initialization_;
};

#endif
