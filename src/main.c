#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <cglm/cglm.h>
#include "shaders/constants.h"
#include "shaders/program.h"

int main()
{
  GLFWwindow *window = initializeGLFW("Cube", 1080, 720);
  if (!window)
  {
    return -1;
  }

  if (initializeGLEW() != 0)
  {
    return -1;
  }

  GLuint vertexShader = compileShader(GL_VERTEX_SHADER, shaderConstants.vertexShaderSource);
  GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, shaderConstants.fragmentShaderSource);

  if (vertexShader == 0 || fragmentShader == 0)
  {
    return -1;
  }

  GLuint shaderProgram = linkShaders(vertexShader, fragmentShader);

  GLuint VAO, VBO, EBO;
  setupBuffers(&VAO, &VBO, &EBO, shaderConstants.vertices, shaderConstants.indices);

  renderLoop(window, shaderProgram, VAO);

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glfwTerminate();

  return 0;
}