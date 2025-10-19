#include "headers/debug.h"
#include "headers/camera.h"
#include "headers/player.h"

void DebugWindow::draw(GLFWwindow* window, Player& player, Camera& camera, float dT)
{
    ImGui::Begin("Debug mode.");

    ImGui::Text("--Player--");
    ImGui::Text("Position: (%.2f, %.2f)", player.pos.x, player.pos.y);
    ImGui::Text("Velocity: (%.2f, %.2f)", player.vel.x, player.vel.y);
    ImGui::Text("On ground: (%s)", player.onGround ? "true" : "false");
    ImGui::Separator();

    ImGui::DragFloat2("Player position edit.", (float*)&player.skin.pos, 1.f);
    ImGui::DragFloat2("Player velocity edit.", (float*)&player.vel, 1.f);
    ImGui::Checkbox("Ghost mode", &player.ghostMode);

    float fps = 1.f / dT;
    ImGui::Text("FPS: %.1f", fps);
    ImGui::Separator();

    ImGui::Text("--=Camera=--");
    ImGui::DragFloat2("Position", (float*)&camera.position, 1.f);
    ImGui::Separator();

    float zoomFactor = 0.5f;
    ImGui::DragFloat("Camera zoom factor", &camera.zoom);
    ImGui::Separator();

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    int tileX = static_cast<int>(mouseX) / 16;
    int tileY = static_cast<int>(mouseY) / 16;

    ImGui::Text("Mouse position: (%.2f, %.2f)", mouseX, mouseY);
    ImGui::Text("Mouse position in tiles: (%i, %i)", tileX, tileY);

    ImGui::End();
}