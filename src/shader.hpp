//
// Created by Felix Moeran on 21/08/2023.
//

#pragma once
#include <string>
#include <map>
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
    // must be called directly after adding ALL the shaders
    void buildProgram();
    void use();

    int getUniformLocation(char* name);
private:
    unsigned int ID;
    std::map<std::string, int> uniformLocations;

    void setDefaultUniforms();
};



