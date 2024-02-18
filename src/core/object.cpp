//
// Created by felix on 02/09/2023.
//

#include "object.hpp"
#include <iostream>
#include <map>
namespace slt
{

    namespace files
    {
        std::map<VertexEnum, std::string> vertex {
            {VertexEnum::VERTEX, "../src/core/shaders/default.vert" },
            {VertexEnum::VERTEX_COLORED, "../src/core/shaders/vertexColoured.vert"}
        };
        std::map<VertexEnum, std::string> fragment {
            {VertexEnum::VERTEX, "../src/core/shaders/default.frag" },
            {VertexEnum::VERTEX_COLORED, "../src/core/shaders/vertexColoured.frag"}
        };
    }


    void Object::setVertices(VertexEnum vertexType, void *vertices, size_t vertSize, void *indices, size_t indSize) {
        _vertices = VertexArray(vertices, vertSize, indices, indSize, vertexType);
    }

    void Object::setShaders(std::string vertexShader, std::string fragmentShader) {
        if (vertexShader.empty()) vertexShader = files::vertex[_vertices.getType()];
        if (fragmentShader.empty()) fragmentShader = files::fragment[_vertices.getType()];
        Shader vert = Shader(vertexShader, ShaderType::VERT);
        Shader frag = Shader(fragmentShader, ShaderType::FRAG);
        _program = ShaderProgram();
        _program.addShader(vert);
        _program.addShader(frag);
        _program.buildProgram();
    }

    void Object::draw(){
        _vertices.draw();
    }

    void Object::setDefaultValues() {
        _worldSpace = vec3(0);
        _rotation = vec3(0);
        _scale = vec3(1);
    }

    glm::mat4 Object::getTransformMatrix() const{
        glm::mat4 matrix(1);
        //float rotationMag = _rotation.
        //matrix = glm::rotate(matrix, _rotation);
        matrix = glm::scale(matrix, _scale);
        matrix = glm::translate(matrix, _worldSpace);
        return matrix;
    }

    void Object::setWorldSpace(vec3 coords) {
        _worldSpace = coords;
    }

    vec3 Object::getWorldSpace() {
        return _worldSpace;
    }

    void Object::setScale(vec3 scales) {
        _scale = scales;
    }

    vec3 Object::getScale() {
        return _scale;
    }

    Object::Object() {
        setDefaultValues();
    }

    void Object::translate(vec3 vec) {
        setWorldSpace(getWorldSpace() + vec);
    }

    void Object::refreshVertices() {
        _vertices.refresh();
    }

}