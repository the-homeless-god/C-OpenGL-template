cmake_minimum_required(VERSION 3.10)

# Project name
project(DigitableGameClient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Executable name and source files
add_executable(
    app

    src/main.c 
    src/shaders/loader.c
    src/shaders/checker.c
    src/shaders/program.c
    src/shaders/constants.c
    src/shaders/matrix.c
)

# Shader files
set(SHADER_FILES
    ${CMAKE_SOURCE_DIR}/src/shaders/assets/vertex_shader.glsl
    ${CMAKE_SOURCE_DIR}/src/shaders/assets/fragment_shader.glsl
)

# Add shader files to the executable
foreach(SHADER_FILE ${SHADER_FILES})
    file(RELATIVE_PATH SHADER_RELATIVE_PATH ${CMAKE_SOURCE_DIR} ${SHADER_FILE})
    get_filename_component(SHADER_OUTPUT_PATH ${SHADER_RELATIVE_PATH} DIRECTORY)

    target_sources(app PRIVATE ${SHADER_FILE})

    add_custom_command(TARGET app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/${SHADER_OUTPUT_PATH}
        COMMAND ${CMAKE_COMMAND} -E copy ${SHADER_FILE} ${CMAKE_BINARY_DIR}/bin/${SHADER_RELATIVE_PATH}
    )
endforeach()

# Link libraries to the executable
target_link_libraries(app ${CONAN_LIBS})

# Setup testing
enable_testing()

file(GLOB TEST_SOURCES "tests/*.test.c")

add_executable(tests ${TEST_SOURCES})

add_test(NAME matrix_tests COMMAND tests)
target_link_libraries(tests ${CONAN_LIBS} CUnit)
