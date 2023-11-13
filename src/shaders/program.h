#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "matrix.h"
#include "checker.h"
#include "loader.h"
#include "constants.h"

#include "types.h"

GLFWwindow *initializeGLFW(const char *window_name, int window_width, int window_height);

void initialize(GLFWwindow **window, const char *window_name, int window_width, int window_height);

int initializeGLEW();
GLuint linkShaders(GLuint vertexShader, GLuint fragmentShader);
GLuint compileShader(GLenum shaderType, const char *source);
void setupBuffers(GLuint *VAO, GLuint *VBO, GLuint *EBO, const float *vertices, const unsigned int *indices);
void renderLoop(GLFWwindow *window, GLuint shaderProgram, GLuint VAO);
