#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D uTexture;
uniform bool uUseTexture;

void main()
{
    if (uUseTexture)
        FragColor = texture(uTexture, TexCoord);
    else
        FragColor = vec4(1.f, 1.f, 1.f, 1.f);
}