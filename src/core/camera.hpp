//
// Created by felix on 01/09/2023.
//

#pragma once

#include "object.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace slt
{
    const vec3  DEFAULT_CAMERA_UP    = {0, 1, 0},
                DEFAULT_CAMERA_FRONT = {0, 0, 1},
                DEFAULT_CAMERA_RIGHT = {1, 0, 0};

    const float DEFAULT_CAMERA_YAW   = 0.0,
                DEFAULT_CAMERA_PITCH = 0.0;

    class Camera {
    public:

        explicit Camera(vec3 position={0.0, 0.0, 0.0}, float fovY=45, float aspectRatio=16.0/9.0, float lowerRangeBound=0.1, float upperRangeBound=100);
        explicit Camera(float fovY=45, vec3 position={0, 0, 0}, float lowerRangeBound=0.1, float upperRangeBound=100);

        /// Draws the given object onto the buffer display ready to be displayed by window::display
        /// \param obj The object to be displayed
        void drawObject(Object& obj);

        /// Draws every object in the scene that wants to be drawn.
        void drawAll();

        /// Sets the camera to have a perspective projection.
        /// \param fovY The angle the camera sees in the y axis.
        /// \param lowerRangeBound The minimum view distance
        /// \param upperRangeBound The maximum view distance
        void setPerspective(float fovY=45, float lowerRangeBound=0.1, float upperRangeBound=100);

        /// Sets the camera to have a perspective projection.
        /// \param fovY The angle the camera sees in the y axis.
        /// \param aspectRatio The aspect ratiu, fovx/fovY.
        /// \param lowerRangeBound The minimum view distance
        /// \param upperRangeBound The maximum view distance
        void setPerspective(float fovY=45, float aspectRatio= 16.0 / 9.0, float lowerRangeBound=0.1, float upperRangeBound=100);

        /// Sets the camer ato have an orthographic projection
        /// \param left The left width of the camera
        /// \param right The right width of the camera
        /// \param bottom The bottom height of the camera
        /// \param top The top height of the camera
        /// \param lowerRangeBound The minimum view distance
        /// \param upperRangeBound The maximum view distance
        void setOrthographic(float left=-1, float right=1, float bottom=-1, float top=1, float lowerRangeBound=0.1, float upperRangeBound=100);

        /// Translates the camera's positions relative to global coordinates
        /// \param vec The 3D vector to translate the camera by
        void translate(vec3 vec);

        /// Translates the camera's position relative to its orientation (right, up, forward)
        void relativeTranslate(vec3 vec);

        /// Returns the current position of the camera
        vec3 getPosition();

        /// Sets the yaw (XZ plane rotation)
        /// \param deg The new yaw in degrees
        void setYaw(float deg);

        /// Alters the yaw (XZ plane rotation)
        /// \param deg tThe amount to change the yaw (degrees)
        void rotateYaw(float deg);

        /// Returns the current yaw (XZ plane rotation) of the camera
        [[nodiscard]] float getYaw() const;

        /// Sets the pitch
        /// \param deg the new yaw in degrees
        void setPitch(float deg);

        /// Alters the pitch
        /// \param deg the new pitch in degrees
        void rotatePitch(float deg);

        /// Returns the current pitch of the camera
        [[nodiscard]] float getPitch() const;

        /// Applies WASD _^ movements by default. \n
        /// NOTE window.loadInputs() must be called before this to work
        void pollDefaultMovementInputs(float speed=1.0, float sensitivity=0.2);

    private:
        vec3 _position, _front, _up, _right;
        float _yaw, _pitch;  // Degrees
        glm::mat4 _projection;

        glm::mat4 _getViewMatrix();

        /// Updates _front, _right, _up.
        /// This should always be used after updating _pitch or _yaw
        void _updateVectors();

        /// Sets the shader uniform values specific to the camera. e.g. view & _projection matrices
        /// \param program the shader to set the uniforms to.
        void _setUniforms(ShaderProgram& program);

    };

}

