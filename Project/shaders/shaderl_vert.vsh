#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 color;
layout(location=2) in vec2 textCoord;
//layout(location=3) in vec3 normals;

out Data
{
    vec4 color;
    vec2 textCoord;
} VSOut;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

mat4 pvm;

void main(void)
{
    VSOut.color = model * vec4(color * 0.5 + vec3(0.5),0.0f);
    VSOut.color.a = 1.0f;
    VSOut.textCoord = textCoord;
    pvm = projection * view * model ;
    gl_Position = pvm * vec4(position, 1.0f);
}
