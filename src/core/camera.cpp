//
// Created by felix on 02/09/2023.
//
#include "camera.hpp"

#include "object.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <algorithm>

namespace slt
{

    Camera::Camera(vec3 position, float fovY, float aspectRatio, float lowerRangeBound, float upperRangeBound) {
        _position = position;
        projection = glm::perspective(fovY, aspectRatio, lowerRangeBound, upperRangeBound);
        _setDefaults();
    }

    Camera::Camera(float fovY, vec3 position, float lowerRangeBound, float upperRangeBound) {
        _position = position;
        projection = glm::perspective(fovY, (float)window::getWidth()/(float)window::getHeight(), lowerRangeBound, upperRangeBound);
        _setDefaults();
    }

    void Camera::drawObject(Object& obj) {
        // set the matrix uniform variables
        obj.useShaderProgram();
        int viewLocation = obj._program.getUniformLocation((char*)"uView");
        int projectionLocation = obj._program.getUniformLocation((char*)"uProjection");
        int modelLocation = obj._program.getUniformLocation((char*)"uModel");

        glm::mat4 view = getViewMatrix();

        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(obj.getTransformMatrix()));

        obj._draw();
    }

    void Camera::translate(vec3 vec) {
        _position += vec;
    }

    glm::mat4 Camera::getViewMatrix() {

        return glm::lookAt(_position, _position + _front, _up);
    }

    void Camera::_setDefaults() {
        _up = vec3(0, 1, 0);
        _front = vec3(0, 0, 1);
        _right = vec3(1, 0, 0);
        _yaw = 0;
        _pitch = 0;
        _updateVectors();
    }

    vec3 Camera::getPosition() {
        return _position;
    }

    void Camera::relativeTranslate(vec3 vec) {
        _position += vec.x * _right;
        _position += vec.y * _up;
        _position += vec.z * _front;
    }

    void Camera::pollDefaultMovementInputs(float speed, float sensitivity){
        // keyboard movement
        vec3 relative(0), absolute(0);
        float mul = speed * (float)window::deltaTime();
        relative += vec3(0, 0, 1) * (float)(window::isHeld(Key::W) - window::isHeld(Key::S)) * mul;
        relative += vec3(1, 0, 0) * (float)(window::isHeld(Key::D) - window::isHeld(Key::A)) * mul;
        relativeTranslate(relative);

        absolute += vec3(0, 1, 0) * (float)(window::isHeld(Key::SPACE) - window::isHeld(Key::LEFT_SHIFT)) * mul;
        translate(absolute);

        // mouse movement
        if (window::mouseLocked()) {
            vec2 offset = window::getDeltaMousePos();
            rotateYaw(offset.x * sensitivity);
            setPitch(std::clamp(getPitch() + offset.y * sensitivity, -89.0f, 89.0f));
        }
    }

    void Camera::_updateVectors() {
        _front.x = (float)sin(glm::radians(_yaw)) * (float)cos(glm::radians(_pitch));
        _front.y = (float)sin(glm::radians(_pitch));
        _front.z = (float)cos(glm::radians(_yaw)) * (float)cos(glm::radians(_pitch));

        _front = glm::normalize(_front);
        _right = glm::normalize(glm::cross(_front, vec3(0, 1, 0)));
        _up    = glm::normalize(glm::cross(_right, _front));
    }

    void Camera::setYaw(float deg) {
        _yaw = std::fmod(deg, 360.0f);
        _updateVectors();
    }

    void Camera::rotateYaw(float deg) {
        setYaw(getYaw() + deg);
    }

    float Camera::getYaw() const {
        return _yaw;
    }

    void Camera::setPitch(float deg) {
        _pitch = deg;
        _updateVectors();
    }

    void Camera::rotatePitch(float deg) {
        setPitch(getPitch() + deg);
    }

    float Camera::getPitch() const {
        return _pitch;
    }
}

