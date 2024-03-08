//
// Created by felix on 08/03/2024.
//

#include "rect.hpp"

namespace slt {
    Rect::Rect(slt::vec3 position, float width, float height)
    : _position(position), _width(width), _height(height)
    {
        Object::_setDefaultValues();
        initVertices();
        Object::setShaders();
    }

    void Rect::initVertices() {
        // VERTICES
        _vertices = std::make_unique<VertexPlain[]>(_numVerts);
        float dx = _width / 2, dy = _height/2;
        float x = _position.x, y = _position.y, z = _position.z;
        _vertices[0] = vec3(x - dx, y - dy, z);
        _vertices[1] = vec3(x + dx, y - dy, z);
        _vertices[2] = vec3(x + dx, y + dy, z);
        _vertices[3] = vec3(x - dx, y + dy, z);
        // INDICEs
        _indices = std::make_unique<unsigned int[]>(_numIndices);

        _indices[0] = 0;
        _indices[1] = 1;
        _indices[2] = 2;
        _indices[3] = 0;
        _indices[4] = 3;
        _indices[5] = 2;

        Object::setVertices(VertexEnum::VERTEX_PLAIN,
                            _vertices.get(), sizeof(VertexPlain) * _numVerts,
                            _indices.get(), sizeof(unsigned int) * _numIndices);

    }


} // slt