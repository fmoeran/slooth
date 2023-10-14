//
// Created by felix on 01/09/2023.
//

#pragma once

#include "window.hpp"
#include "object.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera {
public:

    Camera(glm::vec3 position={0, 0, 0}, float fovY=45, float aspectRatio=16.0/9.0, float lowerRangeBound=0.1, float upperRangeBound=100);
    Camera(Window& window, float fovY=45, glm::vec3 position={0, 0, 0}, float lowerRangeBound=0.1, float upperRangeBound=100);


    void drawObject(Object& obj);

private:


    glm::mat4 projection;
    glm::mat4 view;

};


