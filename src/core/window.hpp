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
    /// Initialises slooth. Must be called before ANYTHING in slooth is used.
    void init(unsigned int width, unsigned int height, std::string title = "");

    /// Whether window::init has been called.
    /// This is mainly used in the internals of Slooth to ensure no OpenGL functionality is used before it has been registered
    bool isInit();

    /// whether the user has clicked the close window button OR if window::close was called
    bool shouldClose();

    /// sets shouldClose to true
    void close();

    /// registers all user inputs so they can be accessed via funcions like window::isPressed and window::getMousePos
    void loadInputs();

    /// returns whether a key is being held down
    bool isHeld(Key key);

    /// returns whether a key has "just" been pressed.
    /// return true if the last time this was called it return false and now the key is held
    /// returns false if the key is not being held or last time this was called the key was being held
    bool isPressed(Key key);

    /// fills the buffer display to a full colour
    void fill(float r, float g, float b, float a);

    /// swaps the buffer display with the current display
    void display();

    /// the window's height
    [[nodiscard]] unsigned int getHeight();

    /// the window's width
    [[nodiscard]] unsigned int getWidth();

    /// returns the time since initialisation of the window (seconds)
    [[nodiscard]] double trueTime();

    /// returns the time between initialisation and the last render of a frame (seconds)
    [[nodiscard]] double frameTime();

    ///  returns the time between the most recent frame render and the one before that (seconds)
    [[nodiscard]] double deltaTime();

    /// returns a null shader.
    [[nodiscard]] ShaderProgram& getNullShader();

    /// returns a vector of all of the objects in the scene.
    [[nodiscard]] std::vector<Object*> objectList();

    /// the position of the mouse on the screen.
    vec2 getMousePos();

    /// how much the mouse's position has changed in the last two calls of window::loadInputs
    vec2 getDeltaMousePos();

    /// will allow/disallow the user to move the mouse
    void setMouseLocked(bool shouldLock);

    /// changes the state of the mouse being locked or unlocked
    void toggleMouseLocked();

    /// returns whether the mouse is locked
    bool mouseLocked();

    /// will change slooth to display the wireframes of the objects instead of the whole faces
    void setWireframe(bool displayWireframe);

    /// toggles whether slooth displays the wireframes or the whole faces of the objects
    void toggleWireframe();

    /// returns whether slooth is currently displaying only the wireframes
    bool wireFrame();

    /// Limits (or stops the limiting of) slooth's FPS to the display rate's
    /// \param shouldCap Whether the cap should be done.
    void capFPS(bool shouldCap);

    /// returns the FPS of the window. Technically 1/window::deltaTime()
    double getFPS();

    /// terminates slooth
    void terminate();

    /// Called automatically by every object to add it to the scene's objectList.
    void registerObject(Object& obj);
}

