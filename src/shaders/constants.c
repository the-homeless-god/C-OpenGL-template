#include <GL/glew.h>
#include "constants.h"
#include "types.h"

ShaderConstants shaderConstants = {
    .vertices = {
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,    // top right
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  // bottom left
        -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,   // top left
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,  // bottom right
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // bottom left
        -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f   // top left
    },
    .indices = {
        0, 1, 3, // front face
        1, 2, 3, // front face
        4, 5, 7, // back face
        5, 6, 7, // back face
        4, 5, 0, // right face
        5, 1, 0, // right face
        7, 6, 3, // left face
        6, 2, 3, // left face
        7, 4, 3, // top face
        4, 0, 3, // top face
        1, 5, 2, // bottom face
        5, 6, 2  // bottom face
    },
    .vertexShaderSource = "#version 330 core\n"
                          "layout (location = 0) in vec3 aPos;\n"
                          "layout (location = 1) in vec3 aColor;\n"
                          "out vec3 ourColor;\n"
                          "uniform mat4 u_transformationMatrix;\n"
                          "void main()\n"
                          "{\n"
                          "   gl_Position = u_transformationMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                          "   ourColor = aColor;\n"
                          "}\n\0",
    .fragmentShaderSource = "#version 330 core\n"
                            "in vec3 ourColor;\n"
                            "out vec4 FragColor;\n"
                            "void main()\n"
                            "{\n"
                            "   FragColor = vec4(ourColor, 1.0f);\n"
                            "}\n\0"};
