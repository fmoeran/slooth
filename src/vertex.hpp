//
// Created by Felix Moeran on 21/08/2023.
//

#pragma once

#include <cstddef>

enum class VertexEnum {
    VERTEX, VERTEX_COLORED
};

struct Vertex {
    float position[3];
    Vertex(float x, float y, float z);
};

struct VertexColored {
    float position[3];
    float rgb[3];
    VertexColored(float x, float y, float z, float r, float g, float b);
};


struct VertexArray {
    VertexArray(void *vertices, size_t vertSize, void *indices, size_t indSize, VertexEnum vertexType);

    void draw();

private:
    unsigned int VAO, VBO, EBO;
    size_t vertSize, indSize;

    void initAttribsDefault();
    void initAttribsColored();
};


