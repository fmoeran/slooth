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
        VERTEX_TEXTURED,
        VERTEX_DEFAULT
    };

    /// A vertex that only stores 3d coordinates
    struct VertexPlain {
        vec3 position;
        VertexPlain(float x, float y, float z);
        VertexPlain(vec3 pos);
        VertexPlain();
    };

    /// VertexDefault that stores position and colour components
    struct VertexColored {
        vec3 position;
        vec3 rgb;
        VertexColored(float x, float y, float z, float r, float g, float b);
        VertexColored(vec3 pos, vec3 col);
    };

    /// VertexDefault that stores position and texture coordinates
    struct VertexDefault {
        vec3 position;
        vec3 normal;
        VertexDefault(float x, float y, float z, float nx, float ny, float nz);
        VertexDefault(vec3 pos, vec3 norm);
        VertexDefault();
    };

    /// VertexDefault that stores position, texture coordinates, and normal vector
    struct VertexTextured {
        vec3 position;
        vec2 uvCoords;
        vec3 normal;
        VertexTextured(float x, float y, float z, float u, float v, float nx, float ny, float nz);
        VertexTextured(vec3 pos, vec2 uv, vec3 norm);
        VertexTextured();
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
        void initAttribsTextured();
        void initAttribsDefault();
    };
}


