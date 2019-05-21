#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 textCoord;

out Data
{
    vec3 normal;
    vec2 textCoord;
} VSOut;

mat4 pvm;

void main(void)
{
    VSOut.normal = normal * 0.5 + vec3(0.5);
    VSOut.textCoord = textCoord;
    gl_Position = vec4(position, 1.0f);
}
