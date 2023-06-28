#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "matrix.h"
#include "checker.h"
#include "loader.h"
#include "constants.h"

#include "types.h"

GLuint compile_shader(GLenum shaderType, const char *source);
GLuint* createShaderProgram();
GLuint create_program(GLuint vertexShader, GLuint fragmentShader);
GLFWwindow initGLFW(const char *window_name, int window_width, int window_height);

Buffers *initBuffers();
void cleanup(GLFWwindow *window);

void render(GLFWwindow *window, GLuint shaderProgram, GLint u_windowHeight, GLint VAO);
void initialize(GLFWwindow **window, const char *window_name, int window_width, int window_height);

int initGLEW();
