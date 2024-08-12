//
// Created by Felix Moeran on 12/08/2024.
//

#include "light.hpp"
#include <string>

namespace slt
{
    PointLight::PointLight() : _position(0), _ambience(DEFAULT_LIGHT_AMBIENCE),
    _diffuse(DEFAULT_LIGHT_DIFFUSE), _specular(DEFAULT_LIGHT_SPECULAR),
    _constantAtt(DEFAULT_ATTENUATION_CONSTANT), _linearAtt(DEFAULT_ATTENUATION_LINEAR),
    _quadraticAtt(DEFAULT_ATTENUATION_QUADRATIC){}

    PointLight::PointLight(vec3 pos): _position(pos), _ambience(DEFAULT_LIGHT_AMBIENCE),
    _diffuse(DEFAULT_LIGHT_DIFFUSE), _specular(DEFAULT_LIGHT_SPECULAR),
    _constantAtt(DEFAULT_ATTENUATION_CONSTANT), _linearAtt(DEFAULT_ATTENUATION_LINEAR),
    _quadraticAtt(DEFAULT_ATTENUATION_QUADRATIC){}


    PointLight::PointLight(vec3 pos, vec3 ambience, vec3 diffuse, vec3 specular)
    : _position(pos), _ambience(ambience), _diffuse(diffuse), _specular(specular),
    _constantAtt(DEFAULT_ATTENUATION_CONSTANT), _linearAtt(DEFAULT_ATTENUATION_LINEAR),
    _quadraticAtt(DEFAULT_ATTENUATION_QUADRATIC){}

    void PointLight::setUniforms(ShaderProgram& program, std::string name) {
        glUniform3f(program.getUniformLocation(name+".pos"), _position.x, _position.y, _position.z);
        glUniform3f(program.getUniformLocation(name+".ambience"), _ambience.x, _ambience.y, _ambience.z);
        glUniform3f(program.getUniformLocation(name+".diffuse"), _diffuse.x, _diffuse.y, _diffuse.z);
        glUniform3f(program.getUniformLocation(name+".specular"), _specular.x, _specular.y, _specular.z);

        glUniform1f(program.getUniformLocation(name+".constAtt"), _constantAtt);
        glUniform1f(program.getUniformLocation(name+".linAtt"), _linearAtt);
        glUniform1f(program.getUniformLocation(name+".quadAtt"), _quadraticAtt);
    }

    void PointLight::setAttenuation(float constant, float linear, float quadratic) {
        _constantAtt  = constant;
        _linearAtt    = linear;
        _quadraticAtt = quadratic;
    }

    void PointLight::setAttenuation(float range) {
        setAttenuation(1.0, 4.5f/range, 75.0f/(range*range));
    }

}
