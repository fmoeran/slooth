//
// Created by felix on 02/09/2023.
//
#include "camera.hpp"

#include "object.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

namespace slt
{

    Camera::Camera(vec3 position, float fovY, float aspectRatio, float lowerRangeBound, float upperRangeBound) {
        _position = position;
        projection = glm::perspective(fovY, aspectRatio, lowerRangeBound, upperRangeBound);
        setDefaults();
    }

    Camera::Camera(Window &window, float fovY, vec3 position, float lowerRangeBound, float upperRangeBound) {
        _position = position;
        projection = glm::perspective(fovY, (float)window.getWidth()/(float)window.getHeight(), lowerRangeBound, upperRangeBound);
        setDefaults();
    }

    void Camera::drawObject(Object& obj) {
        // set the matrix uniform variables
        int viewLocation = obj._program.getUniformLocation((char*)"uView");
        int projectionLocation = obj._program.getUniformLocation((char*)"uProjection");
        int modelLocation = obj._program.getUniformLocation((char*)"uModel");

        glm::mat4 view = getViewMatrix();

        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(obj.getTransformMatrix()));

        obj.draw();
    }

    void Camera::translate(vec3 vec) {
        _position += vec;
    }

    glm::mat4 Camera::getViewMatrix() {
        glm::mat4 view(1);
        view = glm::translate(view, _position);

        return view;
    }

    void Camera::setDefaults() {
        _up =       vec3(0, 1, 0);
        _front =    vec3(0, 0, 1);
    }

    vec3 Camera::getPosition() {
        return _position;
    }

    void Camera::relativeTranslate(vec3 vec) {
        _position -= glm::normalize(glm::cross(_up, _front)) * vec.x;
        _position += vec.y * _up;
        _position += vec.z * _front;
//        std::cout << _position.y << std::endl;
//        std::cout << vec.y << std::endl;
    }

    void Camera::pollDefaultMovementInputs(Window& window, float speed){
        vec3 translation(0);
        float mul = speed * window.deltaTime();
        translation += vec3(0, 0, 1) * (float)(window.isPressed(Key::W) - window.isPressed(Key::S)) * mul;
        translation += vec3(1, 0, 0) * (float)(window.isPressed(Key::D) - window.isPressed(Key::A)) * mul;
        relativeTranslate(translation);
    }
}

