#include "config.h"
#include "triangle_mesh.h"

unsigned int make_module(const std::string &filepath, unsigned int module_type);

/// @brief 创建着色器
/// @param vertex_filepath
/// @param fragment_filepath
/// @return
unsigned int make_shader(const std::string &vertex_filepath,
                         const std::string &fragment_filepath) {

  // To store all the shader modules
  std::vector<unsigned int> modules;

  // Add a vertex shader module 顶点着色器模块
  modules.push_back(make_module(vertex_filepath, GL_VERTEX_SHADER));

  // Add a fragment shader module 片段着色器
  modules.push_back(make_module(fragment_filepath, GL_FRAGMENT_SHADER));

  // Attach all the modules then link the program 链接所模块
  // tell opengl to create a shader program
  unsigned int shader = glCreateProgram();
  for (unsigned int shaderModule : modules) {
    // tell opengl to attach the shader module to the shader program
    glAttachShader(shader, shaderModule);
  }
  // tell opengl to link the modules of the shader program
  glLinkProgram(shader);

  // Check the linking worked
  int success;
  glGetProgramiv(shader, GL_LINK_STATUS, &success);
  if (!success) {
    char errorLog[1024];
    glGetProgramInfoLog(shader, 1024, NULL, errorLog);
    std::cout << "Shader linking error:\n" << errorLog << '\n';
  }

  // Modules are now unneeded and can be freed
  for (unsigned int shaderModule : modules) {
    // tell opengl to delete the shader module
    glDeleteShader(shaderModule);
  }

  return shader;
}

unsigned int make_module(const std::string &filepath,
                         unsigned int module_type) {

  std::ifstream file;
  std::stringstream bufferedLines;
  std::string line;

  file.open(filepath);
  while (std::getline(file, line)) {
    // std::cout << line << std::endl;
    bufferedLines << line << '\n';
  }
  std::string shaderSource = bufferedLines.str();
  const char *shaderSrc = shaderSource.c_str();
  bufferedLines.str("");
  file.close();

  // create a shader module
  unsigned int shaderModule = glCreateShader(module_type);
  glShaderSource(shaderModule, 1, &shaderSrc, NULL);
  // tell opengl to compile the shader module
  glCompileShader(shaderModule);

  int success;
  glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
  if (!success) {
    char errorLog[1024];
    glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
    std::cout << "Shader Module compilation error:\n" << errorLog << std::endl;
  }

  return shaderModule;
}

int main() {

  GLFWwindow *window;

  // 如果这个函数调用成功，您应该在应用程序退出之前调用glfwTerminate
  if (!glfwInit()) {
    return -1;
  }

  // 配置glfw
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // opengl 主版本号
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 次版本号
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 使用核心模式
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); // mac系统下

  // 创建一个窗口及其相关的OpenGL或OpenGL ES上下文
  window = glfwCreateWindow(640, 480, "Hello Window!", NULL, NULL);

  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window); // 将窗口的上下文设置为当前线程上下文

  // GLAD是用来管理OpenGL的函数指针，所以在调用任何OpenGL的函数之前我们需要初始化GLAD
  // 给GLAD传入了用来加载系统相关的OpenGL函数指针地址的函数
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    glfwTerminate();
    return -1;
  }

  glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

  TriangleMesh *triangle = new TriangleMesh();

  unsigned int shader =
      make_shader("../test/what_are_shaders/shaders/vertex.txt",
                  "../test/what_are_shaders/shaders/fragment.txt");

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shader);

    triangle->draw();

    glfwSwapBuffers(window);
  }

  // delete the shader program
  glDeleteProgram(shader);
  glfwTerminate();
  return 0;
}
