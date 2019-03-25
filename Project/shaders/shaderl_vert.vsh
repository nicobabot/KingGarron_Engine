#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 color;

out Data
{
    vec3 color;
} VSOut;

uniform mat4 mat_model;
uniform mat4 projection_view;

void main(void)
{
    VSOut.color = color;
    gl_Position = projection_view * vec4(position, 1.0f);
}
