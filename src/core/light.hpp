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
                DEFAULT_LIGHT_DIFFUSE  = 0.8,
                DEFAULT_LIGHT_SPECULAR = 0.5;

    const float DEFAULT_ATTENUATION_CONSTANT  = 1.0,
                DEFAULT_ATTENUATION_LINEAR    = 0.09,
                DEFAULT_ATTENUATION_QUADRATIC = 0.032;

    const vec3 DEFAULT_LIGHT_DIRECTION = {0, -1, 0}; // DOWN

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

    class DirectionalLight {
    public:
        DirectionalLight();
        DirectionalLight(vec3 direction);
        DirectionalLight(vec3 direction, vec3 ambience, vec3 diffuse, vec3 specular);

        void setUniforms(ShaderProgram& program, std::string name);

    private:
        vec3 _direction, _ambience, _diffuse, _specular;
    };

    namespace lightHandler
    {
        const unsigned int MAX_LIGHT_NUM = 8;

        /// Called automatically whenever a PointLight is created
        void registerPointLight(PointLight& light);

        /// Called automatically whenever a DirectionalLight is created
        void registerDirectionalLight(DirectionalLight& light);

        void setUniforms(ShaderProgram& program);
    }
}