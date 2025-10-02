#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "headers/shader.h"
#include "headers/quad.h"
#include "headers/player.h"
#include "headers/texture.h"
#include "headers/world.h"


void input(GLFWwindow* window, glm::vec2& pos, float velocity)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) pos.y += velocity;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) pos.y -= velocity;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) pos.x -= velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) pos.x += velocity;
}

std::vector<std::vector<Quad>> quadLand(int size)
{
    std::vector<std::vector<Quad>> col;
    for (int i = 0; i < size; ++i)
    {
        std::vector<Quad> row;
        for (int j = 0; j < size; ++j)
        {
            Quad quad(glm::vec2(i * 16.f, j * 16.f), 1.f, 0.f, 16.f, 16.f, nullptr, 0, 0);
            row.push_back(quad);
        }

        col.push_back(row);
    }

    return col;
}

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

    //stbi_set_flip_vertically_on_load(true); 

    int tileX = 0;
    int tileY = 0;

    Shader shader("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");
    shader.use();
    Texture texture("textures/tiles/stone.png", 16, 16);

    Quad playerSkin(glm::vec2(0.f, 300.f), 1.f, 0.f, 30.f, 30.f, nullptr, 0.f, 0.f);
    Player player(playerSkin);

    Quad platform(glm::vec2(400.f, 100.f), 1.f, 0.f, 400.f, 30.f, nullptr, 0, 0);

    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    bool showDebugWindow = false;

    std::vector<std::vector<Quad>> world = quadLand(10);
    World world1(100, 50, static_cast<int>(time(nullptr)), 0.05f);
    world1.generate(texture);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
        GLuint projLoc = glGetUniformLocation(shader.ID, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        shader.use();

        player.update(window, 100.5f, world1.tiles, deltaTime);

        player.draw(shader);
        platform.draw(shader);

        for (auto row : world1.tiles)
        {
            for (Quad block : row)
            {
                block.draw(shader);
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}