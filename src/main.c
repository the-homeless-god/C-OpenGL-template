#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <cglm/cglm.h>
#include "shaders/constants.h"

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "uniform mat4 u_transformationMatrix;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = u_transformationMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\n\0";

const char *fragmentShaderSource =
    "#version 330 core\n"
    "in vec3 ourColor;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0f);\n"
    "}\n\0";

float vertices[] = {
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,    // top right
    0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  // bottom left
    -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,   // top left
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,   // top right
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,  // bottom right
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // bottom left
    -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f   // top left
};

// Define cube indices
unsigned int indices[] = {
    0, 1, 3, // front face
    1, 2, 3, // front face
    4, 5, 7, // back face
    5, 6, 7, // back face
    4, 5, 0, // right face
    5, 1, 0, // right face
    7, 6, 3, // left face
    6, 2, 3, // left face
    7, 4, 3, // top face
    4, 0, 3, // top face
    1, 5, 2, // bottom face
    5, 6, 2  // bottom face
};

int main()
{
  // Initialize GLFW
  if (!glfwInit())
  {
    fprintf(stderr, "Failed to initialize GLFW\n");
    return -1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);               // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

  // Open a window and create its OpenGL context
  GLFWwindow *window;
  window = glfwCreateWindow(1024, 768, "Cube", NULL, NULL);
  if (window == NULL)
  {
    fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  glewExperimental = true; // Needed for core profile
  if (glewInit() != GLEW_OK)
  {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return -1;
  }

  // Compile and bind shaders
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // Check shaders for errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
  }
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
  }

  // Create Vertex Array Object
  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // Create Vertex Buffer Object and copy vertex data
  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Create Element Buffer Object and copy index data
  GLuint EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // Define vertex data layout
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Initialize transformation matrix
  mat4 transformationMatrix;
  glm_mat4_identity(transformationMatrix);

  // Enable depth testing
  glEnable(GL_DEPTH_TEST);

  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window))
  {
    // Clear the colorbuffer and depthbuffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Bind our shader program and vertex array object
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    // Apply transformations
    glm_rotate(transformationMatrix, (float)glfwGetTime() * 0.001f, (vec3){0.5f, 1.0f, 0.0f});

    // Send transformation matrix to the vertex shader
    int transformationMatrixLocation = glGetUniformLocation(shaderProgram, "u_transformationMatrix");
    glUniformMatrix4fv(transformationMatrixLocation, 1, GL_FALSE, &transformationMatrix[0][0]);

    // Draw the cube
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Clean up
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glfwTerminate();

  return 0;
}
