#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "headers/shader.h"
#include "headers/quad.h"
#include "headers/player.h"
#include "ImGui/imgui.h"
#include "ImGui/backends/imgui_impl_glfw.h"
#include "ImGui/backends/imgui_impl_opengl3.h"

void input(GLFWwindow* window, glm::vec2& pos, float velocity)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) pos.y += velocity;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) pos.y -= velocity;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) pos.x -= velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) pos.x += velocity;
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

    Shader shader("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");
    shader.use();

    Quad playerSkin(glm::vec2(400.f, 300.f), 1.f, 0.f, 30.f, 30.f);
    Player player(playerSkin);

    Quad platform(glm::vec2(400.f, 100.f), 1.f, 0.f, 400.f, 30.f);

    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    bool showDebugWindow = false;

    IMGUI_CHECKVERSION();
    /*ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");*/

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        /*if (glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS) 
        {
            static bool wasPressed = false;
            if (!wasPressed) 
            {
                showDebugWindow = !showDebugWindow; 
                wasPressed = true;
            }
            else 
            {
                wasPressed = false;
            }
        }

        ImGui::NewFrame();

        if (showDebugWindow) 
        {
            ImGui::Begin("Debug");
            ImGui::Text("Player pos: (%.1f, %.1f)", player.skin.pos.x, player.skin.pos.y);
            ImGui::Text("Vel: (%.2f, %.2f)", player.vel.x, player.vel.y);
            //ImGui::Checkbox("Show colliders", &showColliders);
            ImGui::End();
        }

        ImGui::Render();*/

        glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
        GLuint projLoc = glGetUniformLocation(shader.ID, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        shader.use();

        player.update(window, 50.5f, platform, deltaTime);

        player.draw(shader);
        platform.draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}