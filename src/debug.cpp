#include "headers/debug.h"

void DebugWindow::draw(Player& player, float dT)
{
    ImGui::Begin("Debug mode.");

    ImGui::Text("--Player--");
    ImGui::Text("Position: (%.2f, %.2f)", player.skin.pos.x, player.skin.pos.y);
    ImGui::Text("Velocity: (%.2f, %.2f)", player.vel.x, player.vel.y);
    ImGui::Separator();

    ImGui::DragFloat2("Player position edit.", (float*)&player.skin.pos, 1.f);
    ImGui::DragFloat2("Player velocity edit.", (float*)&player.vel, 1.f);

    float fps = 1.f / dT;
    ImGui::Text("FPS: %.1f", fps);
    ImGui::Separator();

    ImGui::End();
}