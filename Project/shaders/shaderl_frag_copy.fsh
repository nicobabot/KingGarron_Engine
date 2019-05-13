#version 330 core

in Data
{
    vec3 normal;
    vec2 textCoord;
} FSIn;

//in vec3 FragPos;

uniform sampler2D ourTexture;

uniform sampler2D normalMap;

uniform int typeOfRender=0;

//uniform vec3 cameraPos;

out vec4 outColor;
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

    float specularStrength = 0.5;

   /* vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normalsInText);
    float spec = pow(max(dot(viewDir, normalsInText), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;*/

    albedoAmbientLight.rgb = albedoAmbient.rgb + albedo.rgb * dot(lightDir,normalsInText) * lightColor;
    albedoAmbientLight.a = 1.0f;

    outColor = albedoAmbientLight;
    }
    else{
        outColor = albedo;
    }
}
