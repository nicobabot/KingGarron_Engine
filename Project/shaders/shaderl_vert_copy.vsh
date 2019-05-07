#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 color;
layout(location=2) in vec2 textCoord;

out Data
{
    vec3 color;
    vec2 textCoord;
} VSOut;



mat4 pvm;

void main(void)
{
    //VSOut.color = color;
    VSOut.textCoord = textCoord;
    gl_Position = vec4(position, 1.0f);
}
