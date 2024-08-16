//
// Created by felix on 12/02/2024.
//

#include "plane.hpp"
#include <iostream>

namespace slt
{
    Plane::Plane(vec3 position, vec2 dimensions, ivec2 vertexCounts)
            :Object(), _width(dimensions.x), _length(dimensions.y), _numVertsX(vertexCounts.x), _numVertsZ(vertexCounts.y),
            _numVerts(vertexCounts.x * vertexCounts.y), _numIndices(2 * 3 * (_numVertsX - 1) * (_numVertsZ - 1)){
        Object::setWorldSpace(position);
        initVertices();
        Object::setShaders();
    }

    void Plane::initVertices() {
        assert(_numVertsX > 1 && _numVertsZ > 1);

        // INIT VERTICES

        vec3 bottomLeft = vec3(-_width / 2, 0, -_length / 2);
        float singleQuadWidth  = _width / (float)(_numVertsX - 1);
        float singleQuadLength = _length / (float)(_numVertsZ - 1);
        _vertices = std::make_unique<VertexDefault[]>(_numVerts);

        for (size_t index=0; index<_numVerts; index++) {
            float xOffset = singleQuadWidth * (float)(index % _numVertsX);
            float zOffset = singleQuadLength * (float)(index / _numVertsX);
            _vertices[index].position = bottomLeft + vec3(xOffset, 0, zOffset);
            _vertices[index].normal   = vec3(0, 1, 0);
        }

        // INIT INDICES

        _indices = std::make_unique<unsigned int[]>(_numIndices);

        size_t index = 0;
        for (size_t row=0; row<_numVertsZ-1; row++) {
            for (size_t col=0; col<_numVertsX-1; col++, index += 6) {
                size_t vertexIndex = row * _numVertsX + col;
                _indices[index]   = vertexIndex;
                _indices[index+1] = vertexIndex + 1;
                _indices[index+2] = vertexIndex + 1 + _numVertsX;
                _indices[index+3] = vertexIndex;
                _indices[index+4] = vertexIndex + _numVertsX;
                _indices[index+5] = vertexIndex + 1 + _numVertsX;
            }
        }

        Object::setVertices(VertexEnum::VERTEX_DEFAULT,
                            _vertices.get(), sizeof(VertexDefault) * _numVerts,
                            _indices.get(), sizeof(unsigned int) * _numIndices);
    }
}