#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 textCoord;

out Data
{
    vec3 normal;
    vec2 textCoord;
} VSOut;

//out vec3 FragPos;

//uniform mat4 model;

mat4 pvm;

void main(void)
{
    VSOut.normal = normal;
    VSOut.textCoord = textCoord;
    gl_Position = vec4(position, 1.0f);

    //FragPos = vec3(model * vec4(position, 1.0));
}
