#version 330 core

in Data
{
    vec3 normal;
    vec2 textCoord;
} FSIn;

uniform sampler2D ourTexture;
uniform sampler2D normalMap;
uniform sampler2D depthMap;
uniform vec3 samples[64];
uniform int typeOfRender=0;
uniform vec2 viewport_size;
uniform mat4 viewMatInv;
uniform mat4 projMatInv;
uniform vec3 cameraPos;

out vec4 outColor;

float znear = 0.1f;
float zfar = 10000.0f;
float specularStrength = 0.5;

vec3 GetPosFragmentWorld()
{
    //depthMap
    float depthValue= texture(depthMap, FSIn.textCoord).z;
    vec3 fragPos;
    fragPos.x = (gl_FragCoord.x / viewport_size.x) * 2 - 1;
    fragPos.y = (gl_FragCoord.y / viewport_size.y) * 2 - 1;
    fragPos.z = depthValue * 2 - 1;
    vec4 viewSpacePos = projMatInv * vec4(fragPos.x,fragPos.y,fragPos.z,1);
    viewSpacePos = viewSpacePos/viewSpacePos.w;

    vec4 worldPos = viewMatInv * viewSpacePos;

    return worldPos.xyz;
}

void main(void)
{
    vec4 albedo = texture2D(ourTexture, FSIn.textCoord);
    vec3 normalsInText = texture(normalMap, FSIn.textCoord).xyz;
    mat4 viewMat = inverse(viewMatInv);

    vec4 normalView = viewMatInv * vec4(normalsInText.xyz, 1.0f);

    vec3 tangent = cross(normalView.xyz, vec3(0,1,0));
    vec3 bitangent = cross(normalView.xyz, tangent);
    mat3 TBN = mat3(tangent, bitangent, normalView.xyz);

    //I don't know WATAFAAA IS GOING ON
    float radius = 1.0f;

    float occlussion = 0.0;

    for(int i=0; i<64; ++i)
    {
        // convert sample offset from tangent to view space
        vec3 offSetView = TBN * samples[i];

        //Im not sure if fragPosView is this transformation
        //or just the view mat * the gl_FragCoord
        vec4 coordFrag = vec4(gl_FragCoord.xyz, 1.0f);
        vec4 viewCoord = viewMatInv * coordFrag;

        // texture look-up on the depthmap and reconstruct the sampled position
        vec3 samplePosView = viewCoord.xyz  + offSetView * radius;
        vec3 sampledPosView = GetPosFragmentWorld();

        occlussion += (samplePosView.z < sampledPosView.z - 0.02 ? 1.0 : 0.0);
    }

    outColor = vec4(1.0 - occlussion / 64.0);
}
