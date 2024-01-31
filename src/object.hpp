//
// Created by felix on 02/09/2023.
//

#pragma once

#include "vertex.hpp"
#include "shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Object {
public:
    Object() = default;

    void setVertices(VertexEnum vertexType, void *vertices, size_t vertSize, void *indices, size_t indSize);
    void setShaders(std::string vertexShader = "../src/shaders/default.vert", std::string fragmentShader = "../src/shaders/default.frag");


    void draw();

private:
    VertexArray _vertices;
    ShaderProgram _program;
    glm::vec3 _worldSpace;
    glm::vec3 _rotation;
    glm::vec3 _scale;

    void setDefaultValues();

    glm::mat4 getTransformMatrix();


    friend class Camera;

};




