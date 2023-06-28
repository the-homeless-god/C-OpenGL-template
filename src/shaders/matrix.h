#include <stdio.h>
#include "types.h"

void printMatrix(const Mat4 *matrix);
void identity(Mat4 *matrix);
void translate(Mat4 *matrix, float x, float y, float z);
void rotateX(Mat4 *matrix, float angle);
void rotateY(Mat4 *matrix, float angle);
void rotateZ(Mat4 *matrix, float angle);
void multiply(const Mat4 *left, const Mat4 *right, Mat4 *result);
void scale(Mat4 *matrix, float scaleX, float scaleY, float scaleZ);
void scaleVertices(float *vertices, int vertexCount, float scaleX, float scaleY, float scaleZ);
