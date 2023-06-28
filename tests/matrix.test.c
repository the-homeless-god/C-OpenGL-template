#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include <string.h>

#include "macroses.c"
#include "math.h"

#include "../src/shaders/matrix.c"

int init_suite(void)
{
    return 0;
}

int clean_suite(void)
{
    return 0;
}

void test_identity(void)
{
    Mat4 matrix;
    identity(&matrix);

    for (int i = 0; i < 16; i++)
    {
        if (i == 0 || i == 5 || i == 10 || i == 15)
        {
            CU_ASSERT_DOUBLE_EQUAL(matrix.data[i], 1.0f, 0.0001);
        }
        else
        {
            CU_ASSERT_DOUBLE_EQUAL(matrix.data[i], 0.0f, 0.0001);
        }
    }
}

void test_translate(void)
{
    Mat4 matrix;
    float x = 1.0f, y = 2.0f, z = 3.0f;
    translate(&matrix, x, y, z);

    CU_ASSERT_DOUBLE_EQUAL(matrix.data[12], x, 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(matrix.data[13], y, 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(matrix.data[14], z, 0.0001);
}

void test_rotateX(void)
{
    Mat4 matrix;
    float angle = M_PI / 4; // 45 degrees
    rotateX(&matrix, angle);

    CU_ASSERT_DOUBLE_EQUAL(matrix.data[5], cosf(angle), 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(matrix.data[6], -sinf(angle), 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(matrix.data[9], sinf(angle), 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(matrix.data[10], cosf(angle), 0.0001);
}

void test_rotateY(void)
{
    Mat4 matrix;
    float angle = M_PI / 4.0; // 45 degrees

    rotateY(&matrix, angle);

    CU_ASSERT_DOUBLE_EQUAL(matrix.data[0], cosf(angle), 0.001);
    CU_ASSERT_DOUBLE_EQUAL(matrix.data[2], sinf(angle), 0.001);
    CU_ASSERT_DOUBLE_EQUAL(matrix.data[8], -sinf(angle), 0.001);
    CU_ASSERT_DOUBLE_EQUAL(matrix.data[10], cosf(angle), 0.001);
}

void test_rotateZ(void)
{
    Mat4 matrix;
    float angle = M_PI / 4.0; // 45 degrees

    rotateZ(&matrix, angle);

    CU_ASSERT_DOUBLE_EQUAL(matrix.data[0], cosf(angle), 0.001);
    CU_ASSERT_DOUBLE_EQUAL(matrix.data[1], -sinf(angle), 0.001);
    CU_ASSERT_DOUBLE_EQUAL(matrix.data[4], sinf(angle), 0.001);
    CU_ASSERT_DOUBLE_EQUAL(matrix.data[5], cosf(angle), 0.001);
}

void test_printMatrix(void)
{
    // Testing the printMatrix function might be more challenging, as it prints to the standard output.
    // Instead, we could redirect standard output to a temporary file and check its content.
    FILE *temp = tmpfile();
    Mat4 matrix = {.data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};

    // Redirect stdout to temp
    FILE *orig_stdout = stdout;
    stdout = temp;
    printMatrix(&matrix);
    stdout = orig_stdout; // Restore stdout

    rewind(temp); // Move file pointer back to the beginning

    // Now we check the contents of the file
    char line[100];

    for (int i = 0; i < 4; i++)
    {
        fgets(line, 100, temp);
        // The line should be in the format "X.XX X.XX X.XX X.XX \n"
        for (int j = 0; j < 4; j++)
        {
            float value;
            char *endptr;
            value = strtof(line, &endptr);
            if (endptr == line)
            {
                fprintf(stderr, "Failed to parse float at row %d, column %d\n", i, j);
                return;
            }
            CU_ASSERT_EQUAL(value, matrix.data[i * 4 + j]);
            memmove(line, endptr, strlen(endptr) + 1); // Move the remainder of the line to the start
        }
    }

    fclose(temp);
}

void test_multiply(void)
{
    Mat4 left, right, result;
    identity(&left);
    identity(&right);
    translate(&right, 1.0f, 2.0f, 3.0f);
    multiply(&left, &right, &result);

    // Expect result to be equal to right since left is an identity matrix
    for (int i = 0; i < 16; i++)
    {
        CU_ASSERT_DOUBLE_EQUAL(result.data[i], right.data[i], 0.0001);
    }
}

void test_scale(void)
{
    Mat4 matrix;
    float scaleX = 2.0f, scaleY = 3.0f, scaleZ = 4.0f;
    scale(&matrix, scaleX, scaleY, scaleZ);

    CU_ASSERT_DOUBLE_EQUAL(matrix.data[0], scaleX, 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(matrix.data[5], scaleY, 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(matrix.data[10], scaleZ, 0.0001);
}

void test_scaleVertices(void)
{
    float vertices[] = {1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f};
    int vertexCount = 2;
    float scaleX = 2.0f, scaleY = 3.0f, scaleZ = 4.0f;
    scaleVertices(vertices, vertexCount, scaleX, scaleY, scaleZ);

    CU_ASSERT_DOUBLE_EQUAL(vertices[0], 2.0f, 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(vertices[1], 3.0f, 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(vertices[2], 4.0f, 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(vertices[3], 4.0f, 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(vertices[4], 6.0f, 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(vertices[5], 8.0f, 0.0001);
}

int init_matrix_tests()
{
    CU_pSuite suite;

    ADD_SUITE(suite, "test_matrix");

    ADD_TEST(suite, test_identity);
    ADD_TEST(suite, test_translate);
    ADD_TEST(suite, test_rotateX);
    ADD_TEST(suite, test_rotateY);
    ADD_TEST(suite, test_rotateZ);
    ADD_TEST(suite, test_multiply);
    ADD_TEST(suite, test_scale);
    ADD_TEST(suite, test_scaleVertices);
    ADD_TEST(suite, test_printMatrix);

    return 0;
}
