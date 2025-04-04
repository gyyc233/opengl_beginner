#include "shader.h"
#include <iostream>

// Function prototypes
void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// The MAIN function, from here we start the application and run the game loop
int main() {
  // Init GLFW
  glfwInit();
  // Set all the required options for GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  // Create a GLFWwindow object that we can use for GLFW's functions
  GLFWwindow *window =
      glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    glfwTerminate();
    return -1;
  }

  // Set the required callback functions
  glfwSetKeyCallback(window, key_callback);

  // Define the viewport dimensions
  glViewport(0, 0, WIDTH, HEIGHT);

  // Build and compile our shader program
  Shader ourShader("../test/shader_test/shaders/vertex.vs",
                   "../test/shader_test/shaders/fragment.frag");

  // Set up vertex data (and buffer(s)) and attribute pointers
  GLfloat vertices[] = {
      // Positions         // Colors [R,G,B]
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Right
      -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom Left
      0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // Top
  };

  GLfloat vertices_reversed[] = {// Positions         // Colors
                                 0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f,
                                 -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, 0.0f,
                                 0.0f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f};

  GLuint VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and
  // attribute pointer(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_reversed), vertices_reversed,
               GL_STATIC_DRAW);

  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                        (GLvoid *)0);
  glEnableVertexAttribArray(0);
  // Color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                        (GLvoid *)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0); // Unbind VAO

  float offset_x = 0.1f;
  float offset_y = 0.0f;

  // Game loop
  while (!glfwWindowShouldClose(window)) {
    // Check if any events have been activiated (key pressed, mouse moved etc.)
    // and call corresponding response functions
    glfwPollEvents();

    // Render
    // Clear the colorbuffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the triangle
    ourShader.Use();

    // offset
    GLint vertex_offset_location =
        glGetUniformLocation(ourShader.Program, "offset_x");
    glUniform1f(vertex_offset_location, offset_x);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    offset_x += 0.0001f;
    if (offset_x >= 0.5f)
      break;

    // Swap the screen buffers
    glfwSwapBuffers(window);
  }
  // Properly de-allocate all resources once they've outlived their purpose
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  // Terminate GLFW, clearing any resources allocated by GLFW.
  glfwTerminate();
  return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}
