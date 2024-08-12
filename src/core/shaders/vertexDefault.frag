#version 330 core

in vec3 fragPos;
in vec3 fragNormal;

out vec4 FragColor;

struct Material {
    vec3 ambience;
    vec3 diffuse;
    vec3 specular;
    float shine;
};

struct Light {
    vec3 pos;
    vec3 ambience;
    vec3 diffuse;
    vec3 specular;

    float constAtt;
    float linAtt;
    float quadAtt;
};

uniform vec3  uViewPos;
uniform float uTime;
uniform Material uMaterial;
uniform Light uLight;

vec4 calculateLightIntensity(Light lightSource) {
    vec3 toLightSource      = normalize(lightSource.pos - fragPos);
    float distToLightSource = length(lightSource.pos - fragPos);
    vec3 toViewPos          = normalize(uViewPos - fragPos);
    vec3 reflection         = normalize(2*dot(toLightSource, fragNormal) * fragNormal - toLightSource);

    vec3 ambienceResult = uMaterial.ambience * lightSource.ambience;

    vec3 diffuseResult  = clamp(dot(toLightSource, fragNormal), 0, 1) * lightSource.diffuse * uMaterial.diffuse;

    vec3 specularResult = pow(clamp(dot(reflection, toViewPos), 0, 1), uMaterial.shine) * lightSource.specular * uMaterial.specular;

    float attenuation = 1.0 / (lightSource.constAtt + lightSource.linAtt * distToLightSource +
                        lightSource.quadAtt * distToLightSource * distToLightSource);

    ambienceResult  *= attenuation;
    diffuseResult  *= attenuation;
    specularResult *= attenuation;

    return vec4(ambienceResult + diffuseResult + specularResult, 1.0);
}

void main() {
    FragColor = calculateLightIntensity(uLight) ;
}
