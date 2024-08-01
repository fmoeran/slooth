//
// Created by felix on 02/09/2023.
//

#pragma once

#include "vertex.hpp"
#include "shader.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>
#include <utility>


namespace slt
{
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


        //VertexEnum getVertexType();

        void useShaderProgram();

        void refreshVertices();

        void setWorldSpace(vec3 coords);
        void translate(vec3 vec);
        vec3 getWorldSpace();


        void setScale(vec3 scales);
        vec3 getScale();

        /// Sets the colour of a PLAIN vertex object.
        /// Will not have any effect for any other vertex.
        /// \param clr rgba colour of object (each value 0-1)
        void setPlainColour(vec4 clr);

        /// Sets the colour of a PLAIN vertex object.
        /// Will not have any effect for any other vertex.
        /// \param r red [0-1]
        /// \param g green [0-1]
        /// \param b blue [0-1]
        /// \param a alpha [0-1]
        void setPlainColour(float r, float g, float b, float a=1.0);
        /// Sets the colour of a PLAIN vertex object.
        /// Will not have any effect for any other vertex.
        /// \param r red [0-255]
        /// \param g green [0-255]
        /// \param b blue [0-255]
        /// \param a alpha [0-255]
        void setPlainColour(int r, int g, int b, int a=255);

        vec4 getPlainColour();

    protected:
        VertexArray _vertices;
        ShaderProgram _program;
        vec3 _worldSpace{}, _rotation{}, _scale{};

        // Vertex specific uniforms
        vec4 _plainColour{};

        /// When initializing the object, this sets many of the values like location and position and colour
        /// to default values (usually 0 or 1).
        void _setDefaultValues();

        [[nodiscard]] glm::mat4 getTransformMatrix() const;


         /// Sets the basic uniforms like uTime. \n
         /// Also sets the uniforms for specific vertex types like uColour for VERTEX_PLAIN
         void _setUniforms();

         void _setPlainUniforms();

        friend class Camera;

 private:

     /// Draws the object to the current un-rendered screen. \n
     /// Should only be called by Camera::drawObject. \n
     /// Object._program.use() must be called before this with the uniforms set
     void _draw();

    };
}





