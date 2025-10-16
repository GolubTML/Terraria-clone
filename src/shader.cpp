#include "headers/shader.h"

Shader::Shader(const char* vertex, const char* fragment)
{
    std::string vSrc = loadShader(vertex);
    std::string fSrc = loadShader(fragment);

    const char* vCode = vSrc.c_str();
    const char* fCode = fSrc.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vCode, NULL);
    glCompileShader(vertexShader);
    checkShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fCode, NULL);
    glCompileShader(fragmentShader);
    checkShader(fragmentShader);

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    checkProgram(ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() 
{ 
    glUseProgram(ID); 
}

void Shader::checkShader(GLuint shader)
{
    int success;
    char infLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infLog);
        std::cerr << infLog << std::endl;
        throw std::runtime_error("ERROR::SHADER::COMPILATION_FAILED\n");
    }
}

void Shader::checkProgram(GLuint program)
{
    int success;
    char infLog[512];

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infLog);
        std::cerr << infLog << std::endl;
        throw std::runtime_error("ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n");
    }
}

std::string Shader::loadShader(const char* path)
{
    std::fstream file(path);

    if (!file.is_open()) 
    {
        throw std::runtime_error(std::string("Failed to open shader file: ") + path);
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    
    return buffer.str();
}