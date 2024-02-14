//
// Created by felix on 12/02/2024.
//

#include "plane.hpp"

slt::Plane::Plane(slt::vec3 position, float width, float height, unsigned int numQuadsX, unsigned int numQuadsY) {
    Object::_worldSpace = position;

}
