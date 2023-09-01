//
// Created by Felix Moeran on 21/08/2023.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>




Shader::Shader(std::string fileLocation, ShaderType shaderType)
:type(shaderType), location(std::move(fileLocation)){
    load();
    compile();
}

// retrieves the respective GL_XXX_SHADER for a given ShaderType
GLenum Shader::getGlShaderType() {
    switch (type){
        case ShaderType::VERT: return GL_VERTEX_SHADER;
        case ShaderType::FRAG: return GL_FRAGMENT_SHADER;
    }
}

void Shader::load() {

    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(location);
        std::stringstream ss;
        ss << file.rdbuf();
        file.close();
        sourceCode = ss.str();
    }catch(std::ifstream::failure &e){
        std::cout << "Failed to load shader location: " << location << std::endl;
        throw e;
    }
}

void Shader::compile(){
    GLenum glShaderType = getGlShaderType();
    shader = glCreateShader(glShaderType);
    char* shaderCode = (char*)sourceCode.c_str();
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);

    // check for errors
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success){
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "Shader compilation incomplete:\n" << infoLog << std::endl;
    }

}

Shader::~Shader() {
    glDeleteShader(shader);
}

ShaderProgram::ShaderProgram() {
    ID = glCreateProgram();
}

void ShaderProgram::addShader(Shader& shader){
    glAttachShader(ID, shader.shader);
}

void ShaderProgram::buildProgram(){
    glLinkProgram(ID);
}

void ShaderProgram::use(){
    glUseProgram(ID);
    setDefaultUniforms();
}

int ShaderProgram::getUniformLocation(char *name) {
    return glGetUniformLocation(ID, name);
}

void ShaderProgram::setDefaultUniforms() {
    glUniform1f(getUniformLocation("uTime"), glfwGetTime());
}
