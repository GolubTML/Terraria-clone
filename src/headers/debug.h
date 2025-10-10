#pragma once

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include "player.h"

class Camera;

class DebugWindow
{
public:
    void draw(Player& player, Camera& camera, float dT);
};