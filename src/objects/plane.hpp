//
// Created by felix on 12/02/2024.
//

#pragma once


#include "../core/object.hpp"

namespace slt
{
    class Plane : public Object {
    public:
        Plane(vec3 position, float width, float height, unsigned int numQuadsX, unsigned int numQuadsY);


//        Plane(vec3 position, float width, float height, unsigned int numQuadsX, unsigned int numQuadsY, vec3 forward, vec3 right);
    private:

    };

}
