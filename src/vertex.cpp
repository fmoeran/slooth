//
// Created by Felix Moeran on 21/08/2023.
//

#include "vertex.hpp"
#include <glad/glad.h>
#include<iostream>

namespace slt
{
    Vertex::Vertex(float x, float y, float z) {
        position = {x, y, z};
    }

    Vertex::Vertex(vec3 pos) : position(pos) {}

    VertexColored::VertexColored(float x, float y, float z, float r, float g, float b) {
        position = {x, y, z};
        rgb = {r, g, b};
    }

    VertexColored::VertexColored(vec3 pos, vec3 col): position(pos), rgb(col) {}


    VertexArray::VertexArray() {
        glGenVertexArrays(1, &_VAO);
        glGenBuffers(1, &_VBO);
        glGenBuffers(1, &_EBO);
        _type = VertexEnum::VERTEX;
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
            case VertexEnum::VERTEX:         initAttribsDefault();
            case VertexEnum::VERTEX_COLORED: initAttribsColored();
        }
        glBindVertexArray(0);
    }

    void VertexArray::initAttribsDefault() {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
        glEnableVertexAttribArray(0);
    }

    void VertexArray::initAttribsColored() {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexColored), nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexColored), (void*)(offsetof(VertexColored, rgb)));
        glEnableVertexAttribArray(1);
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


