//
// Created by Felix Moeran on 21/08/2023.
//

#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"


#include <string>
#include <map>
#include <string>
namespace slt
{

    enum class ShaderType {
        FRAG,
        VERT
    };

    class Shader {
    public:
        Shader(std::string fileLocation, ShaderType shaderType);
        ~Shader();
    private:
        unsigned int _shader;
        std::string _sourceCode;
        std::string _location;
        ShaderType _type;


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

        int getUniformLocation(char* name) const;
    private:
        unsigned int _ID;
        std::map<std::string, int> _uniformLocations;
    };
}



