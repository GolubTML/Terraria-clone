#pragma once

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

class Player;
class Camera;

class DebugWindow
{
public:
    void draw(GLFWwindow* window, Player& player, Camera& camera, float dT);
};