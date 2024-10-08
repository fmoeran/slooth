//
// Created by felix on 02/09/2023.
//

#include "object.hpp"
#include "window.hpp"

#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <map>

namespace slt
{

    namespace files
    {
        std::map<VertexEnum, std::string> vertex {
            {VertexEnum::VERTEX_PLAIN,   "../src/core/shaders/vertexPlain.vert" },
            {VertexEnum::VERTEX_COLORED, "../src/core/shaders/vertexColoured.vert"},
            {VertexEnum::VERTEX_DEFAULT, "../src/core/shaders/vertexDefault.vert"}
        };
        std::map<VertexEnum, std::string> fragment {
            {VertexEnum::VERTEX_PLAIN,   "../src/core/shaders/vertexPlain.frag" },
            {VertexEnum::VERTEX_COLORED, "../src/core/shaders/vertexColoured.frag"},
            {VertexEnum::VERTEX_DEFAULT, "../src/core/shaders/vertexDefault.frag"}
        };
    }

    namespace premades
    {
        struct PremadeShader {
            PremadeShader() : program() {}

            explicit PremadeShader(VertexEnum vertexType) : program() {
                Shader vertex(files::vertex[vertexType], ShaderType::VERT);
                Shader fragment(files::fragment[vertexType], ShaderType::FRAG);
                program.addShader(vertex);
                program.addShader(fragment);
                program.buildProgram();
            }
            ShaderProgram program;
        };

        PremadeShader vertPlain;
        PremadeShader vertColoured;
        PremadeShader vertDefault;


        ShaderProgram& getProgram(VertexEnum type) {
            switch (type) {
                case VertexEnum::VERTEX_PLAIN:
                    return vertPlain.program;
                case VertexEnum::VERTEX_COLORED:
                    return vertColoured.program;
                case VertexEnum::VERTEX_DEFAULT:
                    return vertDefault.program;
                case VertexEnum::VERTEX_TEXTURED:
                    return window::getNullShader();
            }
        }
    }

    void initObjectPremades() {
        using namespace premades;
        vertPlain = PremadeShader(VertexEnum::VERTEX_PLAIN);
        vertColoured = PremadeShader(VertexEnum::VERTEX_COLORED);
        vertDefault = PremadeShader(VertexEnum::VERTEX_DEFAULT);
    }

    Object::Object(): _program(window::getNullShader()) {
        window::registerObject(*this);
        _worldSpace     = DEFAULT_OBJECT_POSITION;
        _scale          = DEFAULT_OBJECT_SCALE;
        _rotationVector = DEFAULT_OBJECT_ROTATION_VECTOR;
        _rotationAngle  = DEFAULT_OBJECT_ROTATION_ANGLE;
        _plainColour    = DEFAULT_OBJECT_PLAIN_COLOUR;
        _autoDraw       = DEFAULT_OBJECT_AUTO_DRAW;
    }

    void Object::setVertices(VertexEnum vertexType, void *vertices, size_t vertSize, void *indices, size_t indSize) {
        _vertices = VertexArray(vertices, vertSize, indices, indSize, vertexType);
        if (_program.isNull()) setShaderProgram();
    }

    void Object::setShaderProgram() {
        setShaderProgram(premades::getProgram(_vertices.getType()));
    }

    void Object::setShaderProgram(ShaderProgram &program) {
        _program = program;
    }

    void Object::_draw(){
        _vertices.draw();
    }

    glm::mat4 Object::getTransformMatrix() const{
        glm::mat4 matrix(1);
        matrix = glm::translate(matrix, _worldSpace);
        matrix = glm::rotate(matrix, _rotationAngle, _rotationVector);
        matrix = glm::scale(matrix, _scale);
        return matrix;
    }

    void Object::setWorldSpace(vec3 coords) {
        _worldSpace = coords;
    }

    vec3 Object::getWorldSpace() {
        return _worldSpace;
    }

    void Object::setScale(vec3 scales) {
        _scale = scales;
    }

    vec3 Object::getScale() {
        return _scale;
    }


    void Object::translate(vec3 vec) {
        setWorldSpace(getWorldSpace() + vec);
    }

    void Object::refreshVertices() {
        _vertices.refresh();
    }

    void Object::_useShaderProgram() {
        _program.use();
        _setUniforms();
    }

    void Object::setPlainColour(vec3 clr) {
        material().setDiffuse(clr);
        material().setAmbience(clr);

        _plainColour = clr;
    }

    void Object::setPlainColour(float r, float g, float b) {
        setPlainColour(vec3(r, g, b));
    }

    void Object::setPlainColour(int r, int g, int b) {
        setPlainColour(vec3(r/255, g/255, b/255));
    }

    void Object::_setUniforms() {
        glUniform1f(_program.getUniformLocation("uTime"), (float)glfwGetTime());
        glUniformMatrix4fv(_program.getUniformLocation("uModel"), 1, GL_FALSE, glm::value_ptr(getTransformMatrix()));

        switch (_vertices.getType()) {
            case VertexEnum::VERTEX_PLAIN:
                _setPlainUniforms();
                break;
            case VertexEnum::VERTEX_COLORED:
                break;
            case VertexEnum::VERTEX_TEXTURED:
                break;
            case VertexEnum::VERTEX_DEFAULT:
                _setDefaultUniforms();
                break;
        }
    }

    void Object::_setPlainUniforms() {
        glUniform3f(_program.getUniformLocation("uColour"), _plainColour.r, _plainColour.g, _plainColour.b);
    }

    void Object::_setDefaultUniforms() {
        _material._setUniforms(_program);
    }

    Material &Object::material() {
        return _material;
    }

    bool Object::usesLights() {
        return _vertices.getType() == VertexEnum::VERTEX_DEFAULT || _vertices.getType() == VertexEnum::VERTEX_TEXTURED;
    }

    void Object::setAutoDraw(bool shouldAuto) {
        _autoDraw = shouldAuto;
    }

    bool Object::isAutoDrawing() const {
        return _autoDraw;
    }

    void Object::setRotation(float angle, vec3 vec) {
        _rotationAngle  = angle;
        _rotationVector = vec;
    }

}