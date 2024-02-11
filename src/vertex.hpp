//
// Created by Felix Moeran on 21/08/2023.
//

#pragma once

#include <glm/glm.hpp>

#include <cstddef>
namespace slt
{
    using vec3 = glm::vec3;
    using vec2 = glm::vec2;
    enum class VertexEnum {
        VERTEX, VERTEX_COLORED
    };

    struct Vertex {
        glm::vec3 position;
        Vertex(float x, float y, float z);
        Vertex(vec3 pos);
    };

    struct VertexColored {
        vec3 position;
        vec3 rgb;
        VertexColored(float x, float y, float z, float r, float g, float b);
        VertexColored(vec3 pos, vec3 col);
    };


    struct VertexArray {
        VertexArray();
        VertexArray(void *vertices, size_t vertSize, void *indices, size_t indSize, VertexEnum vertexType);

        void draw();

        void refresh();

        VertexEnum getType();

    private:
        unsigned int _VAO, _VBO, _EBO;
        void* _vertices;
        void* _indices;
        size_t _vertSize, _indSize;
        VertexEnum _type;

        void initAttribsDefault();
        void initAttribsColored();
    };
}


