//
// Created by felix on 02/09/2023.
//

#include "object.hpp"

void Object::setVertices(VertexEnum vertexType, void *vertices, size_t vertSize, void *indices, size_t indSize) {
    VAO = VertexArray(vertices, vertSize, indices, indSize, vertexType);
}

void Object::setShaders(std::string vertexShader, std::string fragmentShader) {
    Shader vert = Shader(vertexShader, ShaderType::VERT);
    Shader frag = Shader(fragmentShader, ShaderType::FRAG);
    program = ShaderProgram();
    program.addShader(vert);
    program.addShader(frag);
    program.buildProgram();
}

void Object::draw() {
    program.use();
    VAO.draw();
}

