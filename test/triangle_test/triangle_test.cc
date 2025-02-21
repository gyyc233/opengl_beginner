// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
// clang-format on
#include <iostream>

#include <vector>

#include <fstream>
#include <sstream>
#include <string>

/// @brief complier shader (vertex ot fragment) 编译着色器
/// @param filepath shader code
/// @param module_type shader type
/// @return shader id
unsigned int make_module(const std::string &filepath, unsigned int module_type);

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
  GLFWwindow *window = NULL;

  GLuint vao;       // 顶点数组对象
  unsigned int vbo; // 顶点缓存对象

  /* geometry to use. these are 3 xyz points (9 floats total) to make a triangle
   */
  GLfloat points[] = {0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f};

  /* these are the strings of code for the shaders
  the vertex shader positions each vertex point */
  std::string vertex_shader = "../test/triangle_test/shaders/vertex.txt";

  /* the fragment shader colours each fragment (pixel-sized area of the
  triangle) */
  std::string fragment_shader = "../test/triangle_test/shaders/fragment.txt";

  /* GL shader objects for vertex and fragment shader [components] */
  GLuint vert_shader, frag_shader;
  /* GL shader programme object [combined, to link] */
  GLuint shader_programme;

  if (!glfwInit()) {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
  if (!window) {
    fprintf(stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    glfwTerminate();
    return -1;
  }

  // 用vbo管理points
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), points, GL_STATIC_DRAW);

  // vao用于定义 在vbo中的哪些数据被用作顶点的输入
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  /* "attribute #0 should be enabled when this vao is bound" */
  glEnableVertexAttribArray(0);
  /* this VBO is already bound, but it's a good habit to explicitly specify
  which VBO's data the following vertex attribute pointer refers to */
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  /* "attribute #0 is created from every 3 variables in the above buffer, of
  type float (i.e. make me vec3s)" */
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  // To store all the shader modules
  std::vector<unsigned int> modules;
  // Add a vertex shader module
  modules.push_back(make_module(vertex_shader, GL_VERTEX_SHADER));
  // Add a fragment shader module
  modules.push_back(make_module(fragment_shader, GL_FRAGMENT_SHADER));

  shader_programme = glCreateProgram();
  glAttachShader(shader_programme, modules[0]);
  glAttachShader(shader_programme, modules[1]);
  glLinkProgram(shader_programme);

  int success;
  glGetProgramiv(shader_programme, GL_LINK_STATUS, &success);
  if (!success) {
    char errorLog[1024];
    glGetProgramInfoLog(shader_programme, 1024, NULL, errorLog);
    std::cout << "Shader linking error:\n" << errorLog << '\n';
  }

  // Modules are now unneeded and can be freed
  for (unsigned int shaderModule : modules) {
    // tell opengl to delete the shader module
    glDeleteShader(shaderModule);
  }

  /* 此循环清除绘图表面，然后将 VAO 描述的几何图形绘制到绘图表面上。
  我们 'poll events' 以查看窗口是否关闭，等等。
  最后，我们 'swap the buffers' 将我们的绘图表面显示到 View 区域。
  我们使用双缓冲系统，这意味着我们有一个 “当前显示” 的表面和 “当前正在绘制的”
  表面。
  因此有了 “交换” 的想法。在单缓冲系统中，我们会看到一个接一个地绘制内容 */

  while (!glfwWindowShouldClose(window)) {
    /* wipe the drawing surface clear 擦除绘图表面 */
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shader_programme);
    glBindVertexArray(vao);
    /* draw points 0-3 from the currently bound VAO with current in-use shader
     */
    // 使用当前正在使用的着色器从当前绑定的 VAO 中绘制点 0-3
    glDrawArrays(GL_TRIANGLES, 0, 3);
    /* update other events like input handling */
    glfwPollEvents();
    /* put the stuff we've been drawing onto the display */
    glfwSwapBuffers(window);
  }

  /* close GL context and any other GLFW resources */
  glfwTerminate();
  return 0;
}
