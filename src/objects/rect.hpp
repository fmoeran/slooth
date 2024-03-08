//
// Created by felix on 08/03/2024.
//

#pragma once

#include "../core/object.hpp"
#include <memory>

namespace slt {

    class Rect: public Object {
    public:
        Rect(vec3 position, float width, float height);
    private:
        vec3 _position;
        float _width, _height;
        static const size_t _numVerts = 4, _numIndices = 6;
        std::unique_ptr<VertexPlain[]> _vertices;
        std::unique_ptr<unsigned int[]> _indices;

        void initVertices();
    };

} // slt


