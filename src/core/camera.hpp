//
// Created by felix on 01/09/2023.
//

#pragma once

#include "window.hpp"
#include "object.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace slt
{

    class Camera {
    public:

        explicit Camera(vec3 position={0, 0, 0}, float fovY=45, float aspectRatio=16.0/9.0, float lowerRangeBound=0.1, float upperRangeBound=100);
        explicit Camera(float fovY=45, vec3 position={0, 0, 0}, float lowerRangeBound=0.1, float upperRangeBound=100);


        void drawObject(Object& obj);

        // translates the camera's positions relative to global coordinates
        void translate(vec3 vec);

        //translates the camera's position relative to its orientation (right, up, forward)
        void relativeTranslate(vec3 vec);

        vec3 getPosition();

        // applies WASD _^ movements by default.
        // note window.loadInputs() must be called before this to work
        void pollDefaultMovementInputs(float speed=1.0, float sensitivity=0.2);


    private:
        vec3 _position, _front, _up, _right;
        float _yaw, _pitch;

        glm::mat4 projection;

        glm::mat4 getViewMatrix();

        void setDefaults();

        void updateVectors();

    };

}

