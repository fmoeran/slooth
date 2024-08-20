//
// Created by Felix Moeran on 21/08/2023.
//

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "window.hpp"

#include "shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>


namespace slt
{
    std::runtime_error NULL_SHADER_EXCEPTION = std::runtime_error("Use of null shader");

    Shader::Shader(std::string fileLocation, ShaderType shaderType)
            :_shader(0), _location(std::move(fileLocation)), _type(shaderType){
        if (!window::isInit()) throw std::runtime_error("Creating a shader before window initialisation.");
        load();
        compile();
    }

// retrieves the respective GL_XXX_SHADER for a given ShaderType
    GLenum Shader::getGlShaderType() {
        switch (_type){
            case ShaderType::VERT: return GL_VERTEX_SHADER;
            case ShaderType::FRAG: return GL_FRAGMENT_SHADER;
        }
    }

    void Shader::load() {

        std::ifstream file;
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            file.open(_location);
            std::stringstream ss;
            ss << file.rdbuf();
            file.close();
            _sourceCode = ss.str();
        }catch(std::ifstream::failure &e){
            std::cout << "Failed to load _shader location: " << _location << std::endl;
            throw e;
        }
    }

    void Shader::compile(){
        GLenum glShaderType = getGlShaderType();
        _shader = glCreateShader(glShaderType);
        char* shaderCode = (char*)_sourceCode.c_str();
        glShaderSource(_shader, 1, &shaderCode, nullptr);
        glCompileShader(_shader);

        // check for errors
        int success;
        glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);
        if (!success){
            char infoLog[512];
            glGetShaderInfoLog(_shader, 512, nullptr, infoLog);
            std::cout << "Shader compilation incomplete:\n" << infoLog << std::endl;
        }
    }

    Shader::~Shader() {
        glDeleteShader(_shader);
    }

    ShaderProgram::ShaderProgram() {
        if (!window::isInit())  makeNull();
        else _ID = glCreateProgram();
    }

    void ShaderProgram::addShader(Shader& shader){
        if (isNull()) throw NULL_SHADER_EXCEPTION;
        glAttachShader(_ID, shader._shader);
    }

    void ShaderProgram::buildProgram(){
        if (isNull()) throw NULL_SHADER_EXCEPTION;
        glLinkProgram(_ID);
    }

    void ShaderProgram::use(){
        if (isNull()) throw NULL_SHADER_EXCEPTION;
        glUseProgram(_ID);
    }

    int ShaderProgram::getUniformLocation(std::string name) {
        if (isNull()) throw NULL_SHADER_EXCEPTION;
        auto it = _uniformLocations.find(name);
        if (it != _uniformLocations.end()) {
            return it->second;
        }else {
            int location = glGetUniformLocation(_ID, name.c_str());
            _uniformLocations[name] = location;
        }
        return _uniformLocations[name];
    }

    bool ShaderProgram::isNull() const {
        return _ID == 0;
    }

    void ShaderProgram::makeNull() {
        _ID = 0;
    }

    int ShaderProgram::numUniformsRegistered() {
        return _uniformLocations.size();
    }

}


