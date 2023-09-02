//
// Created by felix on 02/09/2023.
//

#pragma once

#include "vertex.hpp"
#include "shader.hpp"

class Object {
public:
    Object() = default;

    void setVertices(VertexEnum vertexType, void *vertices, size_t vertSize, void *indices, size_t indSize);
    void setShaders(std::string vertexShader = "../src/shaders/default.vert", std::string fragmentShader = "../src/shaders/default.frag");


    void draw();

private:
    VertexArray VAO;
    ShaderProgram program;

};




