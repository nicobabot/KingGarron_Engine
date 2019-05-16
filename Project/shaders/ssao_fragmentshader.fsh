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

vec3 GetPosFragmentView(float depth)
{
    //depthMap

    vec3 fragPos;
    fragPos.x = (gl_FragCoord.x / viewport_size.x) * 2 - 1;
    fragPos.y = (gl_FragCoord.y / viewport_size.y) * 2 - 1;
    fragPos.z = depth * 2 - 1;
    vec4 viewSpacePos = projMatInv * vec4(fragPos.x,fragPos.y,fragPos.z,1);
    viewSpacePos = viewSpacePos/viewSpacePos.w;

    return viewSpacePos.xyz;
}

void main(void)
{
    vec4 albedo = texture2D(ourTexture, FSIn.textCoord);
    vec3 normalsInText = normalize(texture(normalMap, FSIn.textCoord).xyz * 2.0f - 1.0f);

    mat4 viewMat = inverse(viewMatInv);
    mat4 projMat = inverse(projMatInv);
    //vec4 normalView = viewMatInv * vec4(normalsInText.xyz, 1.0f);

    vec3 tangent = normalize(cross(normalsInText.xyz, vec3(0,1,0)));
    vec3 bitangent = normalize(cross(normalsInText.xyz, tangent));
    mat3 TBN = mat3(tangent, bitangent, normalsInText.xyz);

    float depthValue= texture(depthMap, FSIn.textCoord).z;

    float radius = 0.2f;

    float occlussion = 0.0;

    for(int i=0; i<64; ++i)
    {
        // convert sample offset from tangent to view space
        vec3 offSetWorld = TBN * samples[i];
        vec4 offSetView = viewMat * vec4(offSetWorld, 0.0f);
        // texture look-up on the depthmap and reconstruct the sampled position
        vec3 samplePosView =  GetPosFragmentView(depthValue) + offSetView.xyz * radius;

        vec4 sampleTextCoord = projMat * vec4(samplePosView.xyz, 1.0f);
        sampleTextCoord.xyz/= sampleTextCoord.w;
        sampleTextCoord.xyz = sampleTextCoord.xyz + vec3(0.5f) * 0.5f;

        float sampledDepth = texture(depthMap, sampleTextCoord.xy).z;
        vec3 sampledPosView = GetPosFragmentView(sampledDepth);

        //vec3 sampledPosView = texture(depthMap, FSIn.textCoord).xyz;

        occlussion += (samplePosView.z < sampledPosView.z - 0.02 ? 1.0 : 0.0);
    }

    outColor = vec4(1.0 - occlussion / 64.0);
}
