//
// Created by Felix Moeran on 21/08/2023.
//

#pragma once

#include <glm/glm.hpp>

#include <cstddef>
namespace slt
{

    enum class VertexEnum {
        VERTEX, VERTEX_COLORED
    };

    struct Vertex {
        glm::vec3 position;
        Vertex(float x, float y, float z);
        Vertex(glm::vec3 pos);
    };

    struct VertexColored {
        glm::vec3 position;
        glm::vec3 rgb;
        VertexColored(float x, float y, float z, float r, float g, float b);
        VertexColored(glm::vec3 pos, glm::vec3 col);
    };


    struct VertexArray {
        VertexArray();
        VertexArray(void *vertices, size_t vertSize, void *indices, size_t indSize, VertexEnum vertexType);

        void draw();

        VertexEnum getType();

    private:
        unsigned int _VAO, _VBO, _EBO;
        size_t vertSize, indSize;
        VertexEnum _type;

        void initAttribsDefault();
        void initAttribsColored();
    };
}


