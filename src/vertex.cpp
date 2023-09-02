//
// Created by Felix Moeran on 21/08/2023.
//

#include "vertex.hpp"
#include <glad/glad.h>

Vertex::Vertex(float x, float y, float z) {
    position = {x, y, z};
}

Vertex::Vertex(glm::vec3 pos) : position(pos) {}

VertexColored::VertexColored(float x, float y, float z, float r, float g, float b) {
    position = {x, y, z};
    rgb = {r, g, b};
}

VertexColored::VertexColored(glm::vec3 pos, glm::vec3 col): position(pos), rgb(col) {}

VertexArray::VertexArray(void *vertices, size_t vertSize, void *indices, size_t indSize, VertexEnum vertexType)
: vertSize(vertSize), indSize(indSize){
    // create buffer IDs
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind IDs so that we can initialise them
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // set buffers' data
    glBufferData(GL_ARRAY_BUFFER, vertSize, vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indSize, indices, GL_STATIC_DRAW);

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
    glBindVertexArray(VAO);
    // assumes that the indices are unsigned ints
    glDrawElements(GL_TRIANGLES, indSize/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
}
