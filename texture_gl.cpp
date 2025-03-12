#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include "lib/resource_manager.h"
#include "lib/sprite_renderer.h"

static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}
 
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
    glfwSetErrorCallback(error_callback);

    if(!glfwInit()) exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Texture", primary, NULL);
    // GLFWwindow* window = glfwCreateWindow(mode->width / 2.5, mode->height / 2.5, "Texture", NULL, NULL); // Use this for testing so it doesnt take over the screen
    if(!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ResourceManager::LoadShader("shader/texture/vertex.glsl", "shader/texture/fragment.glsl", nullptr, "sprite");
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", (glm::mat4) glm::ortho(0.0f, static_cast<float>(mode->width), static_cast<float>(mode->height), 0.0f, -1.0f, 1.0f));
    Shader shader = ResourceManager::GetShader("sprite");
    SpriteRenderer* Renderer = new SpriteRenderer(shader);
    ResourceManager::LoadTexture("textures/ball.png", true, "ball");

    while(!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        const float ratio = width / (float) height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        Texture2D ball = ResourceManager::GetTexture("ball");

        xpos -= ball.Width/2;
        ypos -= ball.Height/2;

        if(xpos <= 0) xpos = 0;
        else if(xpos + ball.Width >= width) xpos = width - ball.Width;

        if(ypos <= 0) ypos = 0;
        else if(ypos + ball.Height >= height) ypos = height - ball.Height;

        Renderer->DrawSprite(ball, glm::vec2(xpos, ypos), glm::vec2(64, 64), 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}