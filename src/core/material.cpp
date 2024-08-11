//
// Created by Felix Moeran on 11/08/2024.
//

#include "material.hpp"
namespace slt
{
    float Material::getAmbiance() {
        return _ambience;
    }

    void Material::setAmbience(float ambience) {
        _ambience = ambience;
    }

    float Material::getDiffuse() {
        return _diffuse;
    }

    void Material::setDiffuse(float diffuse) {
        _diffuse = diffuse;
    }

    float Material::getSpecular() {
        return _specular;
    }

    void Material::setSpecular(float specular) {
        _specular = specular;
    }

    float Material::getShine() {
        return _shine;
    }

    void Material::setShine(float shine) {
        _shine = shine;
    }

    Material::Material() : _ambience(DEFAULT_AMBIENCE), _diffuse(DEFAULT_DIFFUSE),
                            _specular(DEFAULT_SPECULAR), _shine(DEFAULT_SHINE){}

    Material::Material(float ambience, float diffuse, float specular, float shine)
    : _ambience(ambience), _diffuse(diffuse), _specular(specular), _shine(shine){}

    void Material::_setUniforms(ShaderProgram& program) {
        glUniform1f(program.getUniformLocation((char*)"uMaterial.ambience"), _ambience);
        glUniform1f(program.getUniformLocation((char*)"uMaterial.diffuse"), _diffuse);
        glUniform1f(program.getUniformLocation((char*)"uMaterial.specular"), _specular);
        glUniform1f(program.getUniformLocation((char*)"uMaterial.shine"), _shine);
    }
}
