#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "matrix.h"
#include "checker.h"
#include "loader.h"
#include "constants.h"
#include "types.h"

GLFWwindow *initializeGLFW(const char *title, int width, int height)
{
  if (!glfwInit())
  {
    fprintf(stderr, "Failed to initialize GLFW\n");
    return NULL;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (window == NULL)
  {
    fprintf(stderr, "Failed to open GLFW window.\n");
    glfwTerminate();
    return NULL;
  }

  glfwMakeContextCurrent(window);

  return window;
}

int initializeGLEW()
{
  // glewExperimental = true;
  if (glewInit() != GLEW_OK)
  {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return -1;
  }

  return 0;
}

GLuint compileShader(GLenum shaderType, const char *source)
{
  GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    printf("Shader compilation failed:\n%s\n", infoLog);
    return 0;
  }

  return shader;
}

GLuint linkShaders(GLuint vertexShader, GLuint fragmentShader)
{
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  return shaderProgram;
}

void setupBuffers(GLuint *VAO, GLuint *VBO, GLuint *EBO, const float *vertices, const unsigned int *indices)
{
  glGenVertexArrays(1, VAO);
  glBindVertexArray(*VAO);

  glGenBuffers(1, VBO);
  glBindBuffer(GL_ARRAY_BUFFER, *VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 8, vertices, GL_STATIC_DRAW); // Замените 8 на количество вершин в вашем массиве

  glGenBuffers(1, EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 36, indices, GL_STATIC_DRAW); // Замените 36 на количество индексов в вашем массиве

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

void renderLoop(GLFWwindow *window, GLuint shaderProgram, GLuint VAO)
{
  glEnable(GL_DEPTH_TEST);
  Mat4 transformationMatrix;
  identity(&transformationMatrix);

  while (!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    // TODO: Use at the finish
    // float angleX = sinf((float)glfwGetTime() * 0.5f) * 0.5f;
    // float angleY = cosf((float)glfwGetTime() * 0.3f) * 0.3f;
    // float angleZ = sinf((float)glfwGetTime() * 0.2f) * 0.2f;

    // rotateX(&transformationMatrix, angleX);
    // rotateY(&transformationMatrix, angleY);
    // rotateZ(&transformationMatrix, angleZ);

    rotateX(&transformationMatrix, (float)glfwGetTime() * 0.003f);
    rotateZ(&transformationMatrix, (float)glfwGetTime() * 0.003f);
    rotateY(&transformationMatrix, (float)glfwGetTime() * 0.003f);

    int transformationMatrixLocation = glGetUniformLocation(shaderProgram, "u_transformationMatrix");
    glUniformMatrix4fv(transformationMatrixLocation, 1, GL_FALSE, transformationMatrix.data);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}
