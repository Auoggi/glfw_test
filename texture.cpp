#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <linmath/linmath.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>

#include "shader/shader.hpp"

int main() {
    if(!glfwInit()) exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);
    // GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Texture", primary, NULL);
    GLFWwindow* window = glfwCreateWindow(mode->width / 2.5, mode->height / 2.5, "Texture", NULL, NULL); // Use this for testing so it doesnt take over the screen
    if(!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

    // [...]

    while(!glfwWindowShouldClose(window)) {
        // [...]

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}