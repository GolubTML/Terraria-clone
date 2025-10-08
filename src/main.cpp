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
#include <chrono>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "headers/shader.h"
#include "headers/quad.h"
#include "headers/player.h"
#include "headers/texture.h"
#include "headers/world.h"
#include "headers/camera.h"
#include "headers/debug.h"

unsigned int getRandomSeed() {
    using namespace std::chrono;
    return static_cast<unsigned int>(
        duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count()
    );
}


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
    glfwSwapInterval(0);

    if (glewInit() != GLEW_OK)
        throw std::runtime_error("Cannot init glew");

    glViewport(0, 0, 800, 600);

    //stbi_set_flip_vertically_on_load(true); 

    bool isPressedDebugMode = false;

    int tileX = 0;
    int tileY = 0;

    Camera camera(800, 600);

    Shader shader("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");
    shader.use();
    Texture stone("textures/tiles/Tiles_1.png", 16, 16);
    Texture dirt("textures/tiles/Tiles_0.png", 16, 16);
    Texture grass("textures/tiles/Tiles_2.png", 16, 16);

    Quad playerSkin(glm::vec2(0.f, 800.f), 1.f, 0.f, 20.f, 48.f, nullptr, 0.f, 0.f);
    Player player(playerSkin);

    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    bool showDebugWindow = false;

    std::vector<std::vector<Quad>> world = quadLand(10);
    World world1(2000, 50, getRandomSeed(), 0.1f);
    world1.generate(dirt, grass);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark(); 

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    static DebugWindow debug;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static float f = 0.0f;
        static int counter = 0;

        if (glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS) isPressedDebugMode = true;
        else isPressedDebugMode = false;

        if (isPressedDebugMode)
            debug.draw(player, deltaTime);

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        camera.move(player.skin.pos - glm::vec2(400.f, 300.f));

        glm::mat4 view = camera.getViewMatrix();
        GLuint viewLoc = glGetUniformLocation(shader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 projection = camera.getProjectionMatrix();
        GLuint projLoc = glGetUniformLocation(shader.ID, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        shader.use();

        player.update(window, 100.5f, world1.tiles, deltaTime);

        player.draw(shader);

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

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();


    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}