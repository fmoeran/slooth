//
// Created by Felix Moeran on 21/08/2023.
//

#pragma once

#include "glm/glm.hpp"

#include <cstddef>
namespace slt
{
    using vec4 = glm::vec4;
    using vec3 = glm::vec3;
    using vec2 = glm::vec2;

    enum class VertexEnum {
        VERTEX_PLAIN,
        VERTEX_COLORED,
        VERTEX_TEXTURE,
        VERTEX_DEFAULT
    };


    // A vertex that only stores 3d coordinates
    struct VertexPlain {
        vec3 position;
        VertexPlain(float x, float y, float z);
        VertexPlain(vec3 pos);
        VertexPlain();
    };

    // Vertex that stores position and colour components
    struct VertexColored {
        vec3 position;
        vec3 rgb;
        VertexColored(float x, float y, float z, float r, float g, float b);
        VertexColored(vec3 pos, vec3 col);
    };

    // Vertex that stores position and texture coordinates
    struct VertexTexture {
        vec3 position;
        vec2 uvCoords;
        VertexTexture(float x, float y, float z, float u, float v);
        VertexTexture(vec3 pos, vec2 uv);
    };

    // Vertex that stores position, texture coordinates, and normal vector
    struct VertexDefault {
        vec3 position;
        vec2 uvCoords;
        vec3 normal;
        VertexDefault(float x, float y, float z, float u, float v, float nx, float ny, float nz);
        VertexDefault(vec3 pos, vec2 uv, vec3 norm);
    };

    struct VertexArray {
        VertexArray();
        VertexArray(void *vertices, size_t vertSize, void *indices, size_t indSize, VertexEnum vertexType);

        void draw();

        void refresh();

        VertexEnum getType();

    private:
        unsigned int _VAO{}, _VBO{}, _EBO{};
        void* _vertices{};
        void* _indices{};
        size_t _vertSize{}, _indSize{};
        VertexEnum _type;

        void initAttribsPlain();
        void initAttribsColored();
        void initAttribsTexture();
        void initAttribsDefault();
    };
}


