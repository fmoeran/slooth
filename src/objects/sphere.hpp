//
// Created by Felix Moeran on 15/08/2024.
//

#pragma once

#include "../core/object.hpp"

#include <memory>

namespace slt
{
    class UVSphere : public Object {
    public:
        /// A sphere made with the UV sphere algorithm.
        /// \param position the 3d position of the sphere's center in space
        /// \param radius the radius of the sphere.
        /// \param precision the square root of the number of the number of vertices in the sphere.
        UVSphere(vec3 position, float radius, size_t precision);
    private:
        float _radius;
        size_t _precision, _numVerts, _numIndices;
        std::unique_ptr<VertexDefault[]> _vertices;
        std::unique_ptr<unsigned int[]> _indices;

        void initVertices();
    };
}
