//
// Created by felix on 02/09/2023.
//

#pragma once

#include "vertex.hpp"
#include "shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace slt
{
 class Object {
    public:
        Object();

        void setVertices(VertexEnum vertexType, void *vertices, size_t vertSize, void *indices, size_t indSize);
        void setShaders(std::string vertexShader = "", std::string fragmentShader = "");

        void refreshVertices();

        void setWorldSpace(vec3 coords);
        void translate(vec3 vec);
        vec3 getWorldSpace();


        void setScale(vec3 scales);
        vec3 getScale();

    private:
        VertexArray _vertices;
        ShaderProgram _program;
        vec3 _worldSpace{};
        vec3 _rotation{};
        vec3 _scale{};

        void setDefaultValues();

        glm::mat4 getTransformMatrix();

         // draws the object to the current un-rendered screen
         // should only be called by Camera::drawObject
         void draw();

        friend class Camera;

    };
}





