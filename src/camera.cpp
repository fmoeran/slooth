//
// Created by felix on 02/09/2023.
//
#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, float fovY, float aspectRatio, float lowerRangeBound, float upperRangeBound) {
    view = glm::mat4(1);
    view = glm::translate(view, position);

    projection = glm::perspective(fovY, aspectRatio, lowerRangeBound, upperRangeBound);
}

Camera::Camera(Window &window, float fovY, glm::vec3 position, float lowerRangeBound, float upperRangeBound) {
    view = glm::mat4(1);
    view = glm::translate(view, position);

    projection = glm::perspective(fovY, (float)window.getWidth()/(float)window.getHeight(), lowerRangeBound, upperRangeBound);
}

