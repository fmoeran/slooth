//
// Created by felix on 12/02/2024.
//

#include "plane.hpp"
#include <iostream>

namespace slt
{
    Plane::Plane(float width, float length, unsigned int numVertsX, unsigned int numVertsZ)
            : _width(width), _length(length), _numVertsX(numVertsX), _numVertsZ(numVertsZ),
            _numVerts(numVertsX * numVertsZ), _numIndices(2 * 3 * (_numVertsX - 1) * (_numVertsZ - 1)){
        Object::_setDefaultValues();
        initVertices();

        Object::setShaders();
    }

    void Plane::initVertices() {
        assert(_numVertsX > 1 && _numVertsZ > 1);

        // INIT VERTICES

        vec3 bottomLeft = vec3(-_width / 2, 0, -_length / 2);
        float singleQuadWidth  = _width / (float)(_numVertsX - 1);
        float singleQuadLength = _length / (float)(_numVertsZ - 1);
        _vertices = std::make_unique<VertexPlain[]>(_numVerts);

        for (size_t index=0; index<_numVerts; index++) {
            float xOffset = singleQuadWidth * (float)(index % _numVertsX);
            float zOffset = singleQuadLength * (float)(index / _numVertsX);
            _vertices[index] = VertexPlain(bottomLeft + vec3(xOffset, 0, zOffset));
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
                _indices[index+3]   = vertexIndex;
                _indices[index+4] = vertexIndex + _numVertsX;
                _indices[index+5] = vertexIndex + 1 + _numVertsX;
            }
        }

        Object::setVertices(VertexEnum::VERTEX_PLAIN,
                            _vertices.get(), sizeof(VertexPlain) * _numVerts,
                            _indices.get(), sizeof(unsigned int) * _numIndices);
    }
}
