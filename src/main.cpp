#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <imgui.h>

#include "headers/shader.h"
#include "headers/quad.h"

int main (int argv, char* args[])
{
    // -- INIT OF GLFW
    if (!glfwInit()) std::cout << "Failed to init GLFW context!" << std::endl;

    // -- Hits foe window and open gl lib, as i undestand
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Terraria", NULL, NULL);
    if (window == NULL)
    {
        throw std::runtime_error("Cannot open GLFW window!");
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        throw std::runtime_error("Cannot init glew");

    glViewport(0, 0, 800, 600);

    Shader shader("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");
    shader.use();

    Quad square(glm::vec2(400.f, 300.f), 1.f, 0.f);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
        GLuint projLoc = glGetUniformLocation(shader.ID, "projection");
        std::cout << "projLoc = " << projLoc << std::endl;
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


        shader.use();

        square.draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}