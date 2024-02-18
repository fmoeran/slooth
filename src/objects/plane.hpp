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
        Plane(float width, float length, unsigned int numVertsX, unsigned int numVertsZ);
    private:
        float _width, _length;
        unsigned int _numVertsX, _numVertsZ;
        size_t _numVerts, _numIndices;
        std::unique_ptr<Vertex[]> _vertices;
        std::unique_ptr<unsigned int[]> _indices;

        // initialises _vertices and _indices arrays and calls Object::setVertices()
        void initVertices();
    };

}
