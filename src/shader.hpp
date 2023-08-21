//
// Created by Felix Moeran on 21/08/2023.
//

#pragma once
#include <string>

enum class ShaderType {
    FRAG,
    VERT
};

class Shader {
public:
    Shader(std::string fileLocation, ShaderType shaderType);
    ~Shader();
private:
    unsigned int shader;
    std::string sourceCode;
    std::string location;
    ShaderType type;


    void load();
    void compile();

    GLenum getGlShaderType();
    friend class ShaderProgram;
};

class ShaderProgram{
public:
    ShaderProgram();
    void addShader(Shader& shader);
    void buildProgram();
    void use();
private:
    unsigned int ID;

};



