#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 color;

out Data
{
    vec3 color;
} VSOut;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

mat4 pvm;

void main(void)
{
    VSOut.color = color;
    pvm = projection * view * model ;
    gl_Position = pvm * vec4(position, 1.0f);
}
