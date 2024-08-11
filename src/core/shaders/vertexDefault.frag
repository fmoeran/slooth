#version 330 core

in vec3 fragPos;
in vec3 fragNormal;

out vec4 FragColor;


struct Material {
    float ambience;
    float diffuse;
    float specular;
    float shine;
};

uniform vec3  uViewPos;
uniform float uTime;
uniform vec4  uColour;
uniform Material uMaterial;

vec3 lightSource = vec3(1, 1, 2);
vec4 lightAmbience = vec4(1);
vec4 lightDiffuse = vec4(1);
vec4 lightSpecular = vec4(1);

void main() {
    vec3 toLightSource = normalize(lightSource - fragPos);
    vec3 toViewPos     = normalize(uViewPos - fragPos);
    vec3 reflection    = normalize(2*dot(toLightSource, fragNormal) * fragNormal - toLightSource);

    vec4 ambienceResult = uMaterial.ambience * lightAmbience;

    vec4 diffuseResult  = clamp(dot(toLightSource, fragNormal), 0, 1) * lightDiffuse * uMaterial.diffuse;

    vec4 specularResult = pow(max(dot(reflection, toViewPos), 0), uMaterial.shine) * lightSpecular * uMaterial.specular;

    FragColor = (ambienceResult + diffuseResult + specularResult) * uColour;
}
