//
// Created by Felix Moeran on 01/08/2024.
//

#pragma once

#include "../core/object.hpp"

namespace slt {

    class Cuboid : public Object {
    public:
        /// A cuboid object.
        /// @param position (x,y,z) position of the cuboid.
        /// @param dimensions (width, height, length)
        Cuboid(vec3 position, vec3 dimensions);
    private:
        vec3 _dimensions;
        static const size_t _numVerts = 8, _numIndices = 36;
        std::unique_ptr<VertexPlain[]> _vertices;
        std::unique_ptr<unsigned int[]> _indices;

        void initVertices();
    };

}


