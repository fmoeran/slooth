//
// Created by Felix Moeran on 21/08/2023.
//

#include "vertex.hpp"
#include "glad/glad.h"
#include<iostream>

namespace slt
{
    VertexPlain::VertexPlain(float x, float y, float z) {
        position = {x, y, z};
    }

    VertexPlain::VertexPlain(vec3 pos) : position(pos) {}

    VertexPlain::VertexPlain() : position(0) {}

    VertexColored::VertexColored(float x, float y, float z, float r, float g, float b) {
        position = {x, y, z};
        rgb = {r, g, b};
    }

    VertexColored::VertexColored(vec3 pos, vec3 col): position(pos), rgb(col) {}

    VertexDefault::VertexDefault(float x, float y, float z, float nx, float ny, float nz) {
        position = {x, y, z};
        normal   = {nx, ny, nz};
    }

    VertexDefault::VertexDefault(vec3 pos, vec3 norm): position(pos), normal(norm) {}

    VertexDefault::VertexDefault(): position(0), normal(0) {}

    VertexTextured::VertexTextured(float x, float y, float z, float u, float v, float nx, float ny, float nz) {
        position = {x, y, z};
        uvCoords = {u, v};
        normal = {nx, ny, nz};
    }
    VertexTextured::VertexTextured(vec3 pos, vec2 uv, vec3 norm): position(pos), uvCoords(uv), normal(norm) {}

    VertexTextured::VertexTextured(): position(0), uvCoords(0), normal(0) {}

    VertexArray::VertexArray() {
        glGenVertexArrays(1, &_VAO);
        glGenBuffers(1, &_VBO);
        glGenBuffers(1, &_EBO);
        _type = VertexEnum::VERTEX_PLAIN;
    }

    VertexArray::VertexArray(void *vertices, size_t vertSize, void *indices, size_t indSize, VertexEnum vertexType)
            : _vertices(vertices), _indices(indices), _vertSize(vertSize), _indSize(indSize){
        _type = vertexType;
        // create buffer IDs
        glGenVertexArrays(1, &_VAO);
        glGenBuffers(1, &_VBO);
        glGenBuffers(1, &_EBO);

        refresh();

        switch (vertexType){
            case VertexEnum::VERTEX_PLAIN:{initAttribsPlain();break;}
            case VertexEnum::VERTEX_COLORED: {initAttribsColored(); break;}
            case VertexEnum::VERTEX_TEXTURED: {initAttribsTextured(); break;}
            case VertexEnum::VERTEX_DEFAULT: {initAttribsDefault(); break;}
        }
        glBindVertexArray(0);
    }

    void VertexArray::initAttribsPlain() {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPlain), nullptr);
        glEnableVertexAttribArray(0);
    }

    void VertexArray::initAttribsColored() {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexColored), nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexColored), (void*)(offsetof(VertexColored, rgb)));
        glEnableVertexAttribArray(1);
    }

    void VertexArray::initAttribsDefault() {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexDefault), nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexDefault), (void*)(offsetof(VertexDefault, normal)));
        glEnableVertexAttribArray(1);
    }

    void VertexArray::initAttribsTextured() {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexTextured), nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexTextured), (void*)(offsetof(VertexTextured, uvCoords)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexTextured), (void*)(offsetof(VertexTextured, normal)));
        glEnableVertexAttribArray(2);
    }

    void VertexArray::draw() {
        glBindVertexArray(_VAO);
        // assumes that the indices are unsigned ints
        glDrawElements(GL_TRIANGLES, _indSize / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
    }

    VertexEnum VertexArray::getType() {
        return _type;
    }

    void VertexArray::refresh() {
        // bind IDs so that we can initialise them
        glBindVertexArray(_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
        // set buffers' data
        glBufferData(GL_ARRAY_BUFFER, (long long)_vertSize, _vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (long long)_indSize, _indices, GL_STATIC_DRAW);
    }
}


