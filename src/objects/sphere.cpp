//
// Created by Felix Moeran on 15/08/2024.
//

#include "sphere.hpp"

#include <cmath>

namespace slt
{

    UVSphere::UVSphere(vec3 position, float radius, size_t precision)
    : Object(), _radius(radius), _precision(precision),
    _numVerts((_precision+1)*(_precision+1)), _numIndices(2 * 3 * _precision * _precision) {
        setWorldSpace(position);
        initVertices();
    }

    void UVSphere::initVertices() {

        _vertices = std::make_unique<VertexDefault[]>(_numVerts);

        for (size_t v=0; v<=_precision; v++) {     // row
            for (size_t u=0; u<=_precision; u++) { // col
                size_t ind = v * (_precision + 1) + u;

                float height = _radius * (float) v / (float) _precision;
                vec3 pos(0);

                float pitch = M_PI * (float) v / (float) _precision - M_PI / 2;
                pos.x = cos(pitch);
                pos.y = sin(pitch);

                float yaw = 2 * M_PI * (float) u / (float) _precision;

                pos.z = sin(yaw) * pos.x;
                pos.x = cos(yaw) * pos.x;

                vec3 normal = pos - vec3({0, height, 0});
                normal = vec3({0, 0, 1});
                _vertices[ind].position = pos;
                _vertices[ind].normal   = pos;
            }
        }

        _indices = std::make_unique<unsigned int[]>(_numIndices);

        size_t index = 0;
        for (size_t row=0; row<_precision; row++) {
            for (size_t col=0; col<_precision; col++, index += 6) {
                size_t vertexIndex = row * (_precision+1) + col;
                _indices[index]   = vertexIndex;
                _indices[index+1] = vertexIndex + 1;
                _indices[index+2] = vertexIndex + _precision + 1;
                _indices[index+3] = vertexIndex + _precision + 2;
                _indices[index+4] = vertexIndex + _precision + 1;
                _indices[index+5] = vertexIndex + 1;
            }
        }

        Object::setVertices(VertexEnum::VERTEX_DEFAULT,
                            _vertices.get(), sizeof(VertexDefault) * _numVerts,
                            _indices.get(), sizeof(unsigned int) * _numIndices);

    }
}
