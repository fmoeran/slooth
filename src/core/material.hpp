//
// Created by Felix Moeran on 11/08/2024.
//

#pragma once

#include "shader.hpp"

namespace slt
{
    const float DEFAULT_AMBIENCE = 0.1,
                DEFAULT_DIFFUSE  = 1.0,
                DEFAULT_SPECULAR = 1.0,
                DEFAULT_SHINE    = 1.0;
    class Material {
    public:
        Material();
        Material(float ambience, float diffuse, float specular, float shine);

        float getAmbiance();
        void setAmbience(float ambience);

        float getDiffuse();
        void setDiffuse(float diffuse);

        float getSpecular();
        void setSpecular(float specular);

        float getShine();
        void setShine(float shine);
    private:
        float _ambience, _diffuse, _specular, _shine;

        void _setUniforms(ShaderProgram& program);

        friend class Object;
    };
}

