#include <GL/glew.h>

#ifndef TYPES_H
#define TYPES_H

typedef struct
{
  GLfloat vertices[12];
  GLuint indices[6];
} ShaderConstants;

typedef struct
{
  float data[16];
} Mat4;

typedef struct
{
  GLuint EBO;
  GLuint VBO;
  GLuint VAO;
} Buffers;

#endif
