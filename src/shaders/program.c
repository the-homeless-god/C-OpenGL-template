#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "matrix.h"
#include "checker.h"
#include "loader.h"
#include "constants.h"
#include "types.h"

GLuint compile_shader(GLenum shaderType, const char *source)
{
  GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);
  checkShaderCompileError(shader);
  return shader;
}

GLuint create_program(GLuint vertexShader, GLuint fragmentShader)
{
  GLuint program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);
  checkProgramLinkError(program);
  return program;
}

void render(GLFWwindow *window, GLuint shaderProgram, GLint u_windowHeight, GLint VAO)
{
  GLint u_transformationMatrix = glGetUniformLocation(shaderProgram, "u_transformationMatrix");

  while (!glfwWindowShouldClose(window))
  {
    // Cleanup color buffer
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    int height, width;
    glfwGetWindowSize(window, &width, &height);

    glUniform1f(u_windowHeight, (float)height);

    Mat4 transformationMatrix;
    identity(&transformationMatrix);

    rotateX(&transformationMatrix, 15.0f);
    rotateZ(&transformationMatrix, 15.0f);
    rotateY(&transformationMatrix, -15.0f);

    glUseProgram(shaderProgram);
    glUniformMatrix4fv(u_transformationMatrix, 1, GL_FALSE, transformationMatrix.data);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Swap buffers to render
    glfwSwapBuffers(window);

    // Keyboard or mouse events
    glfwPollEvents();
  }
}

GLFWwindow *initGLFW(const char *window_name, int window_width, int window_height)
{
  if (!glfwInit())
  {
    fprintf(stderr, "Failed to init GLFW\n");
    return NULL;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(window_width, window_height, window_name, NULL, NULL);
  if (!window)
  {
    fprintf(stderr, "Failed to open GLFW window.\n");
    glfwTerminate();
    return NULL;
  }

  glfwMakeContextCurrent(window);

  return window;
}

int initGLEW()
{
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
  {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return -1;
  }

  return 0;
}
char *readFile(const char *filePath)
{
  long length;
  char *buffer;
  FILE *f = fopen(filePath, "rb");

  if (f)
  {
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length);

    if (buffer)
    {
      fread(buffer, 1, length, f);
      buffer[length] = '\0';
    }
    fclose(f);
  }

  return buffer;
}
GLuint* createShaderProgram()
{
  // TODO: use loader from assets folder
  // seems like the shaders loading is hard to track on current device
  // need to verify that the following code works maybe from other systems

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

  return shaderProgram;
}

void initialize(GLFWwindow **window, const char *window_name, int window_width, int window_height)
{
  *window = initGLFW(window_name, window_width, window_height);
  if (!*window)
  {
    fprintf(stderr, "Failed to initialize GLFW\n");
    return;
  }

  if (initGLEW() != 0)
  {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return;
  }
}

Buffers *initBuffers()
{
  Buffers *buffers = malloc(sizeof(Buffers));

  // Init Vertex Array Object
  glGenVertexArrays(1, &buffers->VAO);
  glBindVertexArray(buffers->VAO);

  // Init Vertex Buffer Object and copy vertex data
  glGenBuffers(1, &buffers->VBO);
  glBindBuffer(GL_ARRAY_BUFFER, buffers->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(shaderConstants.vertices), shaderConstants.vertices, GL_STATIC_DRAW);

  // Init Element Buffer Object and copy index data
  glGenBuffers(1, &buffers->EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(shaderConstants.indices), shaderConstants.indices, GL_STATIC_DRAW);

  // Define vertex data layout
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  return buffers;
}

void cleanup(GLFWwindow *window)
{
  glfwTerminate();
}
