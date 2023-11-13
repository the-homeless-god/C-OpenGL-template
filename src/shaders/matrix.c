#include <stdio.h>
#include <math.h>
#include "types.h"

void printMatrix(const Mat4 *matrix)
{
  for (int i = 0; i < 16; i++)
  {
    printf("%.2f ", matrix->data[i]);
    if ((i + 1) % 4 == 0)
    {
      printf("\n");
    }
  }
  printf("\n");
}

void identity(Mat4 *matrix)
{
  for (int i = 0; i < 16; i++)
  {
    matrix->data[i] = 0.0f;
  }

  matrix->data[0] = 1.0f;
  matrix->data[5] = 1.0f;
  matrix->data[10] = 1.0f;
  matrix->data[15] = 1.0f;
}

void translate(Mat4 *matrix, float x, float y, float z)
{
  identity(matrix);

  matrix->data[12] = x;
  matrix->data[13] = y;
  matrix->data[14] = z;
}

void multiply(const Mat4 *left, const Mat4 *right, Mat4 *result)
{
  for (int row = 0; row < 4; row++)
  {
    for (int col = 0; col < 4; col++)
    {
      float sum = 0.0f;
      for (int k = 0; k < 4; k++)
      {
        sum += left->data[row * 4 + k] * right->data[k * 4 + col];
      }
      result->data[row * 4 + col] = sum;
    }
  }
}

void rotateX(Mat4 *matrix, float angle)
{
  Mat4 rotationMatrix;
  identity(&rotationMatrix);

  float cosVal = cosf(angle);
  float sinVal = sinf(angle);
  rotationMatrix.data[5] = cosVal;
  rotationMatrix.data[6] = -sinVal;
  rotationMatrix.data[9] = sinVal;
  rotationMatrix.data[10] = cosVal;

  multiply(matrix, &rotationMatrix, matrix);
}

void rotateY(Mat4 *matrix, float angle)
{
  Mat4 rotationMatrix;
  identity(&rotationMatrix);

  float cosVal = cosf(angle);
  float sinVal = sinf(angle);
  rotationMatrix.data[0] = cosVal;
  rotationMatrix.data[2] = sinVal;
  rotationMatrix.data[8] = -sinVal;
  rotationMatrix.data[10] = cosVal;

  multiply(matrix, &rotationMatrix, matrix);
}

void rotateZ(Mat4 *matrix, float angle)
{
  Mat4 rotationMatrix;
  identity(&rotationMatrix);

  float cosVal = cosf(angle);
  float sinVal = sinf(angle);
  rotationMatrix.data[0] = cosVal;
  rotationMatrix.data[1] = -sinVal;
  rotationMatrix.data[4] = sinVal;
  rotationMatrix.data[5] = cosVal;

  multiply(matrix, &rotationMatrix, matrix);
}

void scale(Mat4 *matrix, float scaleX, float scaleY, float scaleZ)
{
  matrix->data[0] = scaleX;
  matrix->data[5] = scaleY;
  matrix->data[10] = scaleZ;
}

void scaleVertices(float *vertices, int vertexCount, float scaleX, float scaleY, float scaleZ)
{
  for (int i = 0; i < vertexCount * 3; i += 3)
  {
    vertices[i] *= scaleX;
    vertices[i + 1] *= scaleY;
    vertices[i + 2] *= scaleZ;
  }
}
