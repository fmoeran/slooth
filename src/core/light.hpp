//
// Created by Felix Moeran on 12/08/2024.
//

#pragma once

#include "shader.hpp"
#include "vertex.hpp" // vec3
#include <array>

namespace slt
{
    const float DEFAULT_LIGHT_AMBIENCE = 0.1,
                DEFAULT_LIGHT_DIFFUSE  = 0.5,
                DEFAULT_LIGHT_SPECULAR = 1.0;

    const float DEFAULT_ATTENUATION_CONSTANT  = 1.0,
                DEFAULT_ATTENUATION_LINEAR    = 0.09,
                DEFAULT_ATTENUATION_QUADRATIC = 0.032;

    /// Light class to represent a point of light in space
    class PointLight {
    public:
        PointLight();
        PointLight(vec3 pos);
        PointLight(vec3 pos, vec3 ambience, vec3 diffuse, vec3 specular);
        
        void setUniforms(ShaderProgram& program, std::string name);

        void setAttenuation(float constant, float linear, float quadratic);

        void setAttenuation(float range);
        
    private:
        vec3 _position, _ambience, _diffuse, _specular;
        float _constantAtt, _linearAtt, _quadraticAtt;
    };

    namespace lightHandler
    {
        const unsigned int MAX_LIGHT_NUM = 8;

        /// Called automatically whenever a PointLight is created
        void registerPointLight(PointLight& light);

        void setUniforms(ShaderProgram program);
    }
}