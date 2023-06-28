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
    }};
