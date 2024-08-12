//
// Created by Felix Moeran on 11/08/2024.
//

#include "material.hpp"
namespace slt
{
    vec3 Material::getAmbiance() {
        return _ambience;
    }

    void Material::setAmbience(vec3 ambience) {
        _ambience = ambience;
    }

    vec3 Material::getDiffuse() {
        return _diffuse;
    }

    void Material::setDiffuse(vec3 diffuse) {
        _diffuse = diffuse;
    }

    vec3 Material::getSpecular() {
        return _specular;
    }

    void Material::setSpecular(vec3 specular) {
        _specular = specular;
    }

    float Material::getShine() {
        return _shine;
    }

    void Material::setShine(float shine) {
        _shine = shine;
    }

    Material::Material() : _ambience(DEFAULT_MATERIAL_AMBIENCE), _diffuse(DEFAULT_MATERIAL_DIFFUSE),
                           _specular(DEFAULT_MATERIAL_SPECULAR), _shine(DEFAULT_MATERIAL_SHINE){}

    Material::Material(float ambience, float diffuse, float specular, float shine)
    : _ambience(ambience), _diffuse(diffuse), _specular(specular), _shine(shine){}

    void Material::_setUniforms(ShaderProgram& program) {
        std::string name = "uMaterial";
        glUniform3f(program.getUniformLocation(name+".ambience"), _ambience.x, _ambience.y, _ambience.z);
        glUniform3f(program.getUniformLocation(name+".diffuse"), _diffuse.x, _diffuse.y, _diffuse.z);
        glUniform3f(program.getUniformLocation(name+".specular"), _specular.x, _specular.y, _specular.z);
        glUniform1f(program.getUniformLocation(name+".shine"), _shine);
    }
}
