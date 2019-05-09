#version 330 core

in Data
{
    vec3 color;
    vec2 textCoord;
} FSIn;

uniform sampler2D ourTexture;
layout(location = 0)out vec4 outColor;
layout(location = 1) out vec4 normals;
void main(void)
{
    outColor = texture2D(ourTexture, FSIn.textCoord);
    normals = vec4(FSIn.color, 1.0f);
}
