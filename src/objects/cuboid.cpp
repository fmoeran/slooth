//
// Created by Felix Moeran on 01/08/2024.
//

#include "cuboid.hpp"

#define BIT(x, n) (x>>n)&1

namespace slt{

    Cuboid::Cuboid(vec3 position, vec3 dimensions)
    : Object(), _dimensions(dimensions){
        _worldSpace = position;
        initVertices();
        Object::setShaders();
        Object::setWorldSpace(position);
    }

    void Cuboid::initVertices() {
        // VERTICES
        _vertices = std::make_unique<VertexPlain[]>(_numVerts);
        vec3 d = {_dimensions.x/2, _dimensions.y/2, _dimensions.z/2};
        float mul[] = {1, -1};
        for (int vert=0; vert<_numVerts; vert++) {
            vec3 pos = {mul[BIT(vert, 0)], mul[BIT(vert, 1)], mul[BIT(vert, 2)]};
            pos *= d;
            _vertices[vert] = pos;

        }

        // INDICES
        _indices = std::make_unique<unsigned int[]>(_numIndices);

        unsigned int vals[] = {0, 1, 2,
                               1, 2, 3,
                               0, 4, 5,
                               0, 5, 1,
                               0, 4, 2,
                               6, 4, 2,
                               1, 5, 3,
                               3, 5, 7,
                               2, 6, 3,
                               3, 6, 7,
                               4, 5, 6,
                               5, 6, 7};

        std::fill(_indices.get(), _indices.get() + _numIndices, 0);

        std::copy(vals, vals + 36, _indices.get());

        Object::setVertices(VertexEnum::VERTEX_PLAIN,
                            _vertices.get(), sizeof(VertexPlain) * _numVerts,
                            _indices.get(), sizeof(unsigned int) * _numIndices);
    }
}