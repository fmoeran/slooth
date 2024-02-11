//
// Created by felix on 02/09/2023.
//

#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "keys.hpp"
#include "vertex.hpp"


namespace slt::window {
    void init(unsigned int width, unsigned int height, char *title = (char*)"");

    bool shouldClose();

    void loadInputs();

    bool isPressed(Key key);

    void fill(float r, float g, float b, float a);

    void display();

    [[nodiscard]] unsigned int getHeight();

    [[nodiscard]] unsigned int getWidth();

    // returns the time since initialisation of the window
    [[nodiscard]] double time();

    // returns the time between initialisation and the last render of a frame
    [[nodiscard]] double frameTime();

    //  returns the time between the most recent frame render and the one before that
    [[nodiscard]] double deltaTime();

    vec2 getMousePos();

    vec2 getDeltaMousePos();

    void setMouseLocked(bool shouldLock);
    void toggleMouseLocked();

    void close();
}

