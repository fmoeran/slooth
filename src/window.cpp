//
// Created by felix on 02/09/2023.
//
#include "window.hpp"


#include "GLFW/glfw3.h"

#include <iostream>

bool gladLoaded = false;

void loadGlad() {
    if (gladLoaded) return;
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }else {
        gladLoaded = true;
    }
}

void loadGLFW() {
    glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if defined(__APPLE__)
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

namespace slt::window {
    GLFWwindow *_windowPtr = nullptr;
    unsigned int _width, _height;
    double _startupTime, _frameTime, _deltaTime;

    void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }

    void init(unsigned int width, unsigned int height, char *title){
        assert(_windowPtr == nullptr);
        loadGLFW();

        // glfw window creation
        // --------------------
        _windowPtr = glfwCreateWindow(width, height, title, nullptr, nullptr);

        if (_windowPtr == nullptr) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            throw;
        }

        _width = width;
        _height = height;

        glfwMakeContextCurrent(_windowPtr);
        glfwSetFramebufferSizeCallback(_windowPtr, framebufferSizeCallback);

        _startupTime = glfwGetTime();

        loadGlad();
    }

    unsigned int getHeight() {
        return _height;
    }

    unsigned int getWidth() {
        return _width;
    }

    bool shouldClose() {
        return glfwWindowShouldClose(_windowPtr);
    }

    void fill(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void display() {
        glfwSwapBuffers(_windowPtr);

        // update time variables
        double t = time();
        _deltaTime = t - _frameTime;
        _frameTime = time();
    }

    double time() {
        return glfwGetTime() - _startupTime;
    }

    double frameTime() {
        return _frameTime;
    }

    double deltaTime() {
        return _deltaTime;
    }

    void close() {
        glfwSetWindowShouldClose(_windowPtr, true);
    }

    void loadInputs() {
        glfwPollEvents();
    }

    bool isPressed(Key key) {
        return (glfwGetKey(_windowPtr, (int) key) == GLFW_PRESS);
    }


} // namespace slt::window
