//
// Created by felix on 02/09/2023.
//
#include "camera.hpp"

#include "object.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace slt
{

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

    void Camera::drawObject(Object& obj) {
        // set the matrix uniform variables
        int viewLocation = obj._program.getUniformLocation((char*)"view");
        int projectionLocation = obj._program.getUniformLocation((char*)"projection");

        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

        obj.draw();
    }
}

