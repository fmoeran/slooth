//
// Created by Felix Moeran on 01/08/2024.
//

#include "cuboid.hpp"

#define BIT(x, n) ((x>>n)&1)

namespace slt{

    vec3 front = {0, 0, 1}, right = {1, 0, 0}, top = {0, 1, 0};

     const VertexDefault Cuboid::_vertexInitialiser[_numVerts] = {
            // Front Face
            VertexDefault({0.5, 0.5, 0.5}, front), // TOP RIGHT
            VertexDefault({0.5, -0.5, 0.5}, front), // BOTTOM RIGHT
            VertexDefault({-0.5, -0.5, 0.5}, front), // BOTTOM LEFT
            VertexDefault({-0.5, 0.5, 0.5}, front), // TOP LEFT
            // Right Face
            VertexDefault({0.5, 0.5, -0.5}, right), // TOP RIGHT
            VertexDefault({0.5, -0.5, -0.5}, right), // BOTTOM RIGHT
            VertexDefault({0.5, -0.5, 0.5}, right), // BOTTOM LEFT
            VertexDefault({0.5, 0.5, 0.5}, right), // TOP LEFT
            // Top Face
            VertexDefault({0.5, 0.5, -0.5}, top), // TOP RIGHT
            VertexDefault({0.5, 0.5, 0.5}, top), // BOTTOM RIGHT
            VertexDefault({-0.5, 0.5, 0.5}, top), // BOTTOM LEFT
            VertexDefault({-0.5, 0.5, -0.5}, top), // TOP LEFT
             // Back Face
            VertexDefault({0.5, 0.5, -0.5}, -front), // TOP RIGHT
            VertexDefault({0.5, -0.5, -0.5}, -front), // BOTTOM RIGHT
            VertexDefault({-0.5, -0.5, -0.5}, -front), // BOTTOM LEFT
            VertexDefault({-0.5, 0.5, -0.5}, -front), // TOP LEFT
             // Left Face
            VertexDefault({-0.5, 0.5, -0.5}, -right), // TOP RIGHT
            VertexDefault({-0.5, -0.5, -0.5}, -right), // BOTTOM RIGHT
            VertexDefault({-0.5, -0.5, 0.5}, -right), // BOTTOM LEFT
            VertexDefault({-0.5, 0.5, 0.5}, -right), // TOP LEFT
             // Botom Face
            VertexDefault({0.5, -0.5, -0.5}, -top), // TOP RIGHT
            VertexDefault({0.5, -0.5, 0.5}, -top), // BOTTOM RIGHT
            VertexDefault({-0.5, -0.5, 0.5}, -top), // BOTTOM LEFT
            VertexDefault({-0.5, -0.5, -0.5}, -top), // TOP LEFT

    };

    Cuboid::Cuboid(vec3 position, vec3 dimensions)
    : Object(), _dimensions(dimensions){
        initVertices();
        Object::setShaders();
        Object::setWorldSpace(position);
    }

    void Cuboid::initVertices() {

        for (size_t v=0; v<_numVerts; v++) {
            _vertices[v].position = _dimensions * _vertexInitialiser[v].position;
            _vertices[v].normal   = _vertexInitialiser[v].normal;
        }

        const size_t faceSize = 6;
        for (size_t f=0; f<6; f++) {
            unsigned int vInd = f * 4, iInd = f * 6;
            unsigned int faceInds[faceSize] = {vInd + 0, vInd + 1, vInd + 2, vInd + 0, vInd + 3, vInd + 2};
            std::copy(faceInds, faceInds+faceSize, _indices + iInd);
        }

        Object::setVertices(VertexEnum::VERTEX_DEFAULT,
                            _vertices, sizeof(VertexDefault) * _numVerts,
                            _indices, sizeof(unsigned int) * _numIndices);
    }
}