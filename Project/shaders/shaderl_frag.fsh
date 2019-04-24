#version 330 core

in Data
{
    vec3 color;
    vec2 textCoord;
} FSIn;

uniform sampler2D ourTexture;
out vec4 outColor;

void main(void)
{
    outColor = vec4(FSIn.color,1.0);
    //outColor = texture2D(ourTexture, FSIn.textCoord);
}
