#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shaders/program.h"
#include "shaders/constants.h"

int main()
{
  GLFWwindow *window;
  GLuint shaderProgram, VAO;

  const GLubyte *version = glGetString(GL_VERSION);
  printf("OpenGL Version: %s\n", version);

  initialize(&window, &shaderProgram, &VAO, "Cube", 1080, 720);
  setupBuffers(VAO);
  render(window, shaderProgram, glGetUniformLocation(shaderProgram, "u_windowHeight"), VAO);
  cleanup(window);

  return 0;
}
