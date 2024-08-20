//
// Created by Felix Moeran on 12/08/2024.
//

#include "light.hpp"
#include <string>
#include <iostream>

namespace slt
{
    PointLight::PointLight() : _position(0), _ambience(DEFAULT_LIGHT_AMBIENCE),
    _diffuse(DEFAULT_LIGHT_DIFFUSE), _specular(DEFAULT_LIGHT_SPECULAR),
    _constantAtt(DEFAULT_ATTENUATION_CONSTANT), _linearAtt(DEFAULT_ATTENUATION_LINEAR),
    _quadraticAtt(DEFAULT_ATTENUATION_QUADRATIC){
        lightHandler::registerPointLight(*this);
    }

    PointLight::PointLight(vec3 pos): _position(pos), _ambience(DEFAULT_LIGHT_AMBIENCE),
    _diffuse(DEFAULT_LIGHT_DIFFUSE), _specular(DEFAULT_LIGHT_SPECULAR),
    _constantAtt(DEFAULT_ATTENUATION_CONSTANT), _linearAtt(DEFAULT_ATTENUATION_LINEAR),
    _quadraticAtt(DEFAULT_ATTENUATION_QUADRATIC){
        lightHandler::registerPointLight(*this);
    }


    PointLight::PointLight(vec3 pos, vec3 ambience, vec3 diffuse, vec3 specular)
    : _position(pos), _ambience(ambience), _diffuse(diffuse), _specular(specular),
    _constantAtt(DEFAULT_ATTENUATION_CONSTANT), _linearAtt(DEFAULT_ATTENUATION_LINEAR),
    _quadraticAtt(DEFAULT_ATTENUATION_QUADRATIC){
        lightHandler::registerPointLight(*this);
    }

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

    DirectionalLight::DirectionalLight(): _direction(DEFAULT_LIGHT_DIRECTION), _ambience(DEFAULT_LIGHT_AMBIENCE),
    _diffuse(DEFAULT_LIGHT_DIFFUSE), _specular(DEFAULT_LIGHT_SPECULAR){
        lightHandler::registerDirectionalLight(*this);
    }

    DirectionalLight::DirectionalLight(vec3 direction): _direction(direction), _ambience(DEFAULT_LIGHT_AMBIENCE),
    _diffuse(DEFAULT_LIGHT_DIFFUSE), _specular(DEFAULT_LIGHT_SPECULAR) {
        lightHandler::registerDirectionalLight(*this);
    }

    DirectionalLight::DirectionalLight(vec3 direction, vec3 ambience, vec3 diffuse, vec3 specular)
    : _direction(direction), _ambience(ambience), _diffuse(diffuse), _specular(specular)  {
        lightHandler::registerDirectionalLight(*this);
    }

    void DirectionalLight::setUniforms(ShaderProgram &program, std::string name) {
        glUniform3f(program.getUniformLocation(name+".direction"), _direction.x, _direction.y, _direction.z);
        glUniform3f(program.getUniformLocation(name+".ambience"), _ambience.x, _ambience.y, _ambience.z);
        glUniform3f(program.getUniformLocation(name+".diffuse"), _diffuse.x, _diffuse.y, _diffuse.z);
        glUniform3f(program.getUniformLocation(name+".specular"), _specular.x, _specular.y, _specular.z);
    }


    namespace lightHandler
    {
        std::array<PointLight*, MAX_LIGHT_NUM> pointLights;
        std::array<DirectionalLight*, MAX_LIGHT_NUM> directionalLights;
        unsigned int numPointLights = 0, numDirectionalLights = 0;

        bool reachedMaxLightNum() {
            return numPointLights + numDirectionalLights >= MAX_LIGHT_NUM;
        }

        void registerPointLight(PointLight& light) {
            if (reachedMaxLightNum()) throw(std::runtime_error("Too many lights. MAX_LIGHT_NUM = " + std::to_string(MAX_LIGHT_NUM)));
            pointLights[numPointLights] = &light;
            numPointLights++;
        }

        void registerDirectionalLight(DirectionalLight& light) {
            if (reachedMaxLightNum()) throw(std::runtime_error("Too many lights. MAX_LIGHT_NUM = " + std::to_string(MAX_LIGHT_NUM)));
            directionalLights[numDirectionalLights] = &light;
            numDirectionalLights++;
        }

        void setUniforms(ShaderProgram& program) {
            // POINT LIGHTS
            glUniform1i(program.getUniformLocation("uNumPointLights"), numPointLights);
            for (size_t index = 0; index < numPointLights; index++) {
                std::string name = "uPointLights[" + std::to_string(index) + "]";
                PointLight& light = *pointLights[index];
                light.setUniforms(program, name);
            }

            // DIRECTIONAL LIGHTS
            glUniform1i(program.getUniformLocation("uNumDirectionalLights"), numDirectionalLights);
            for (size_t index = 0; index < numDirectionalLights; index++) {
                std::string name = "uDirectionalLights[" + std::to_string(index) + "]";
                DirectionalLight& light = *directionalLights[index];
                light.setUniforms(program, name);
            }
        }
    }

}
