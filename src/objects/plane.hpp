//
// Created by felix on 12/02/2024.
//

#pragma once


#include "../core/object.hpp"


#include <memory>

namespace slt
{
    class Plane : public Object {
    public:
        Plane(vec3 position, vec2 dimensions, ivec2 vertexCounts);
    private:
        float _width, _length;
        unsigned int _numVertsX, _numVertsZ;
        size_t _numVerts, _numIndices;
        std::unique_ptr<VertexDefault[]> _vertices;
        std::unique_ptr<unsigned int[]> _indices;

        /// initialises _vertices and _indices arrays and calls Object::setVertices()
        void initVertices();
    };

}
