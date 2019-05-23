#version 330 core

in Data
{
    vec3 normal;
    vec2 textCoord;
} FSIn;

uniform sampler2D ourTexture;
uniform sampler2D normalMap;
uniform sampler2D depthMap;
uniform sampler2D saoMap;

uniform vec2 viewport_size;
uniform mat4 viewMatInv;
uniform mat4 projMatInv;
uniform vec3 cameraPos;

uniform int typeOfRender=0;
uniform int typeRenderLight=0;

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
    if(typeOfRender == 0)
    {
        outColor = texture2D(ourTexture, FSIn.textCoord);
        return;
    }
    else if(typeOfRender == 1)
    {
        outColor = texture2D(normalMap, FSIn.textCoord);
        return;
    }
    else if(typeOfRender == 2)
    {
        outColor = texture2D(depthMap, FSIn.textCoord);
        return;
    }
    else if(typeOfRender == 3)
    {
        outColor = texture2D(saoMap, FSIn.textCoord);
        return;
    }

    float ambientTerm = 1.0f;

    vec4 albedo;
    vec4 albedoAmbient;
    vec4 albedoAmbientLight;
    vec3 lightDir = vec3(0.0f,0.0f,1.0f);
    vec3 lightColor = vec3(0.1f,0.1f,0.1f);

    albedo = texture2D(ourTexture, FSIn.textCoord);

    float ambientOcc = texture2D(saoMap, FSIn.textCoord).z;

    albedoAmbient = albedo * ambientTerm * ambientOcc;
    albedoAmbient.a = 1.0f;

    if(typeRenderLight == 0){
       outColor = albedoAmbient;
       //return;
    }
    else if(typeRenderLight == 1){

        vec3 normalsInText= normalize(texture(normalMap, FSIn.textCoord).xyz * 2.0f - 1.0f);

        vec3 viewDir = normalize(cameraPos - GetPosFragmentWorld());
        vec3 halfDir = normalize(viewDir + lightDir);
        float spec = pow(max(dot(normalsInText, halfDir), 0.0), 32);
        vec3 specular = specularStrength * spec * lightColor;

        albedoAmbientLight.rgb = (albedo.rgb * dot(lightDir,normalsInText) + specular) * lightColor;
        albedoAmbientLight.a = 1.0f;

        outColor = albedoAmbientLight;
    }

}
