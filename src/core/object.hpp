//
// Created by felix on 02/09/2023.
//

#pragma once

#include "vertex.hpp"
#include "shader.hpp"
#include "material.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>
#include <utility>

namespace slt
{
    const vec3  DEFAULT_OBJECT_POSITION  = {0, 0, 0},
                DEFAULT_OBJECT_SCALE           = {1, 1, 1},
                DEFAULT_OBJECT_ROTATION_VECTOR = {1, 0, 0},
                DEFAULT_OBJECT_PLAIN_COLOUR    = DEFAULT_MATERIAL_DIFFUSE;

    const float DEFAULT_OBJECT_ROTATION_ANGLE = 0.0f;

    const bool DEFAULT_OBJECT_AUTO_DRAW = true;

    class Object {
    public:
        Object();

        /// Sets the object to point to a specific mesh of vertices and the indexes to draw them at
        /// \param vertexType slt::VertexEnum type, specifies what type of vertex is being stored in vertices
        /// \param vertices void pointer to the beginning of the vertices container
        /// \param vertSize number of bytes in vertices
        /// \param indices void pointer to the beginning of the indices container
        /// \param indSize number of bytes in indices
        void setVertices(VertexEnum vertexType, void *vertices, size_t vertSize, void *indices, size_t indSize);

        /// Assigns the specific vertex and fragment shader to use
        /// \param vertexShader relative path to vertex shader, "" sets it to the default shader for the object's vertex type
        /// \param fragmentShader relative path to fragment shader, "" sets it to the default shader for the object's vertex type
        void setShaders(std::string vertexShader = "", std::string fragmentShader = "");

        void useShaderProgram();

        void refreshVertices();

        void setWorldSpace(vec3 coords);
        void translate(vec3 vec);
        vec3 getWorldSpace();

        void setScale(vec3 scales);
        vec3 getScale();

        /// Sets the colour of an object without a texture.
        /// sets the diffuse and ambience of the object's material to this colour
        /// \param clr rgba colour of object (each value 0-1)
        void setPlainColour(vec3 clr);

         /// Sets the colour of an object without a texture.
         /// sets the diffuse and ambience of the object's material to this colour
        /// \param r red [0-1]
        /// \param g green [0-1]
        /// \param b blue [0-1]
        void setPlainColour(float r, float g, float b);

        /// Sets the colour of an object without a texture.
        /// sets the diffuse and ambience of the object's material to this colour
        /// \param r red [0-255]
        /// \param g green [0-255]
        /// \param b blue [0-255]
        void setPlainColour(int r, int g, int b);

        Material& material();

        /// returns whether the object reacts to light.
        bool usesLights();

        /// this determines whether that Camera::drawAll should draw this object.
        void setAutoDraw(bool shouldAuto);
        /// Returns whether this object will be drawn by Camera::drawAll()..
        bool isAutoDrawing();

        [[nodiscard]] glm::mat4 getTransformMatrix() const;
    private:
        VertexArray _vertices;
        ShaderProgram _program;
        vec3 _worldSpace{}, _rotationVector{}, _scale{};
        float _rotationAngle; // radians
        bool _autoDraw;
        // When using VertexPlain
        vec3 _plainColour;

        // When using a vertex that reacts to light
        Material _material;

        /// Sets the basic uniforms like uTime. \n
        /// Also sets the uniforms for specific vertex types like uColour for VERTEX_PLAIN
        void _setUniforms();

        // Sets the uniform values for different types of vertices
        void _setPlainUniforms();
        void _setDefaultUniforms();

         /// Draws the object to the current un-rendered screen. \n
         /// Should only be called by Camera::drawObject. \n
         /// Object._program.use() must be called before this with the uniforms set
         void _draw();


        friend class Camera;

    };
}





