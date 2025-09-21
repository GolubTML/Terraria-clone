#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    GLuint ID;
    Shader(const char* vertex, const char* fragment);
    void use();

private:
    std::string loadShader(const char* path);

    void checkShader(GLuint shader);
    void checkProgram(GLuint program);
};