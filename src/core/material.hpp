//
// Created by Felix Moeran on 11/08/2024.
//

#pragma once

#include "shader.hpp"
#include "vertex.hpp"

namespace slt
{
    const vec3  DEFAULT_MATERIAL_AMBIENCE(0.2),
                DEFAULT_MATERIAL_DIFFUSE(1.0),
                DEFAULT_MATERIAL_SPECULAR(1.0);
    const float DEFAULT_MATERIAL_SHINE    = 32.0;

    class Material {
    public:
        Material();
        Material(float ambience, float diffuse, float specular, float shine);

        vec3 getAmbiance();
        void setAmbience(vec3 ambience);

        vec3 getDiffuse();
        void setDiffuse(vec3 diffuse);

        vec3 getSpecular();
        void setSpecular(vec3 specular);

        float getShine();
        void setShine(float shine);
    private:
        vec3 _ambience, _diffuse, _specular;
        float _shine;

        void _setUniforms(ShaderProgram& program);

        friend class Object;
    };
}

