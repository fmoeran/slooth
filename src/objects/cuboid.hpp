//
// Created by Felix Moeran on 01/08/2024.
//

#pragma once

#include "../core/object.hpp"

namespace slt {

    class Cuboid : public Object {
    public:
        Cuboid();
        /// A cuboid object.
        /// @param position (x,y,z) position of the cuboid.
        /// @param dimensions (width, height, length)
        Cuboid(vec3 position, vec3 dimensions);
    private:
        vec3 _dimensions;
        static const size_t _numVerts = 24, _numIndices = 36;
        static const VertexDefault _vertexInitialiser[];
        VertexDefault _vertices[_numVerts];
        unsigned int _indices[_numIndices];

        void initVertices();
    };

}


