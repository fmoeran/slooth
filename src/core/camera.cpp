//
// Created by felix on 02/09/2023.
//
#include "camera.hpp"
#include "object.hpp"
#include "light.hpp"
#include "window.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <algorithm>

namespace slt
{

    Camera::Camera(vec3 position, float fovY, float aspectRatio, float lowerRangeBound, float upperRangeBound) {
        _position = position;
        _projection = glm::perspective(fovY, aspectRatio, lowerRangeBound, upperRangeBound);
        _up = DEFAULT_CAMERA_UP;
        _front = DEFAULT_CAMERA_FRONT;
        _right = DEFAULT_CAMERA_RIGHT;
        _yaw = DEFAULT_CAMERA_YAW;
        _pitch = DEFAULT_CAMERA_PITCH;
        _updateVectors();
    }

    Camera::Camera(float fovY, vec3 position, float lowerRangeBound, float upperRangeBound) {
        _position = position;
        setPerspective(fovY, (float)window::getWidth()/(float)window::getHeight(), lowerRangeBound, upperRangeBound);
        _up = DEFAULT_CAMERA_UP;
        _up = {0, 1, 0};
        _front = DEFAULT_CAMERA_FRONT;
        _front = {0, 0, 1};
        _right = DEFAULT_CAMERA_RIGHT;
        _right = {1, 0, 0};
        _yaw = DEFAULT_CAMERA_YAW;
        _pitch = DEFAULT_CAMERA_PITCH;
        _updateVectors();
    }

    void Camera::drawObject(Object& obj) {
        obj._useShaderProgram();
        _setUniforms(obj._program);

        if (obj.usesLights()) lightHandler::setUniforms(obj._program);

        obj._draw();
    }

    void Camera::setPerspective(float fovY, float lowerRangeBound, float upperRangeBound) {
        setPerspective(fovY, (float)window::getWidth() / (float)window::getHeight(), lowerRangeBound, upperRangeBound);
    }

    void Camera::setPerspective(float fovY, float aspectRatio, float lowerRangeBound, float upperRangeBound) {
        _projection = glm::perspective(fovY, aspectRatio, lowerRangeBound, upperRangeBound);
    }

    void Camera::setOrthographic(float left, float right, float bottom, float top, float lowerRangeBound, float upperRangeBound) {
        _projection = glm::ortho(left, right, bottom, top, 0.1f, 100.0f);
    }

    void Camera::translate(vec3 vec) {
        _position += vec;
    }

    glm::mat4 Camera::_getViewMatrix() {
        return glm::lookAt(_position, _position + _front, _up);
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

    void Camera::_setUniforms(ShaderProgram& program) {
    
        int viewMatLocation = program.getUniformLocation("uView");
        int projMatLocation = program.getUniformLocation("uProjection");
        int viewPosLocation  = program.getUniformLocation("uViewPos");

        glm::mat4 view = _getViewMatrix();

        glUniformMatrix4fv(viewMatLocation, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projMatLocation, 1, GL_FALSE, glm::value_ptr(_projection));
        glUniform3f(viewPosLocation, getPosition().x, getPosition().y, getPosition().z);
    }

    void Camera::drawAll() {
        for (Object* obj : window::objectList()) {
            if (obj->isAutoDrawing()) {
                drawObject(*obj);
            }
        }
    }
}

