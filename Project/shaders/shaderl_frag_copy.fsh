#version 330 core

in Data
{
    vec3 normal;
    vec2 textCoord;
} FSIn;

uniform sampler2D ourTexture;
uniform sampler2D normalMap;
uniform int typeOfRender=0;
uniform vec2 viewport_size;
uniform mat4 viewMat;
uniform mat4 projMat;
uniform vec3 cameraPos;

out vec4 outColor;

float znear = 0.1f;
float zfar = 10000.0f;
float specularStrength = 0.5;

vec3 GetPosFragmentWorld()
{
    vec4 posFrag;
    posFrag.xy = ((2.0 * gl_FragCoord.xy) / viewport_size.xy) - 1;
    posFrag.z = ((2.0 * gl_FragCoord.z) - (zfar - znear)) / (zfar - znear);
    posFrag.w = 1.0;
    posFrag /= gl_FragCoord.w;

    vec4 WordPosFrag = viewMat * projMat * posFrag;
    return WordPosFrag.xyz;
}

void main(void)
{
    //outColor = vec4(FSIn.color,1.0);

    float ambientTerm = 0.05f;

    vec4 albedo;
    vec4 albedoAmbient;
    vec4 albedoAmbientLight;
    vec3 lightDir = vec3(0.0f,0.0f,1.0f);
    vec3 lightColor = vec3(1.0f,1.0f,1.0f);


    albedo = texture2D(ourTexture, FSIn.textCoord);
     if(typeOfRender==0){
    albedoAmbient = albedo * ambientTerm;
    albedoAmbient.a = 1.0f;

    vec3 normalsInText= texture(normalMap, FSIn.textCoord).xyz;

    vec3 viewDir = normalize(cameraPos - GetPosFragmentWorld());
    vec3 reflectDir = normalize(viewDir + lightDir);
    float spec = pow(max(dot(normalsInText, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    albedoAmbientLight.rgb = albedoAmbient.rgb + albedo.rgb * dot(lightDir,normalsInText) + specular * lightColor;
    albedoAmbientLight.a = 1.0f;

    outColor = albedoAmbientLight;
    }
    else{
        outColor = albedo;
    }
}
