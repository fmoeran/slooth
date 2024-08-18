//
// Created by felix on 02/09/2023.
//

#pragma once

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "keys.hpp"
#include "vertex.hpp"
#include "object.hpp"


namespace slt::window {
    void init(unsigned int width, unsigned int height, char *title = (char*)"");

    bool isInit();

    bool shouldClose();

    void loadInputs();

    /// returns whether a key is being held down
    bool isHeld(Key key);

    /// returns whether a key has "just" been pressed.
    /// return true if the last time this was called it return false and now the key is held
    /// returns false if the key is not being held or last time this was called the key was being held
    bool isPressed(Key key);

    void fill(float r, float g, float b, float a);

    void display();

    [[nodiscard]] unsigned int getHeight();

    [[nodiscard]] unsigned int getWidth();

    /// returns the time since initialisation of the window (seconds)
    [[nodiscard]] double trueTime();

    /// returns the time between initialisation and the last render of a frame (seconds)
    [[nodiscard]] double frameTime();

    ///  returns the time between the most recent frame render and the one before that (seconds)
    [[nodiscard]] double deltaTime();

    /// returns the number of frames per second if deltaTime() was consistent.
    [[nodiscard]] double fps();

    /// returns a null shader.
    [[nodiscard]] ShaderProgram& getNullShader();

    /// returns a vector of all of the objects in the scene.
    [[nodiscard]] std::vector<Object*> objectList();

    vec2 getMousePos();

    vec2 getDeltaMousePos();

    void setMouseLocked(bool shouldLock);
    void toggleMouseLocked();
    bool mouseLocked();

    void setWireframe(bool displayWireframe);
    void toggleWireframe();
    bool wireFrame();

    void capFPS(bool shouldCap);
    double getFPS();

    void close();

    void terminate();

    /// Called automatically by every object to add it to the objectList.
    void registerObject(Object& obj);

}

