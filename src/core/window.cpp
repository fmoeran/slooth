//
// Created by felix on 02/09/2023.
//
#include "window.hpp"
#include "vertex.hpp"


#include "GLFW/glfw3.h"

#include <iostream>
#include <cstring>

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
    bool _isInit = false;
    GLFWwindow *_windowPtr = nullptr;
    unsigned int _width, _height;
    double _startupTime, _frameTime, _deltaTime;
    vec2 _mousePos, _frameMousePos, _deltaMousePos;
    bool _isFirstFrame, _isMouseLocked, _ignoreNextMouseMovement, _mouseMovedThisFrame;
    bool _keyPressed[(size_t) Key::NUM_KEYS];
    bool _isWireframe;
    std::vector<Object*> _objectList;
    std::unique_ptr<ShaderProgram> _nullShaderProgram;

    void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }

    void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
        _mousePos = {xpos, ypos};
        _mouseMovedThisFrame = true;
    }

    void clearPressedLogs() {
        std::memset(_keyPressed, 0, sizeof(_keyPressed));
    }

    void init(unsigned int width, unsigned int height, char *title) {
        assert(_windowPtr == nullptr);
        loadGLFW();

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
        glfwSetCursorPosCallback(_windowPtr, mouseCallback);

        _startupTime = glfwGetTime();

        _isFirstFrame = true;
        _ignoreNextMouseMovement = true;

        clearPressedLogs();

        loadGlad();

        glEnable(GL_DEPTH_TEST);

        _nullShaderProgram = std::make_unique<ShaderProgram>();
        _nullShaderProgram->makeNull();

        _isInit = true;

        initObjectPremades();
    }

    bool isInit() {
        return _isInit;
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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    std::vector<Object*> objectList() {
        return _objectList;
    }


    void updateMouseVariables() {
        vec2 newPos = _mousePos;
        if (_ignoreNextMouseMovement) {
            _deltaMousePos = vec2(0);
            if (_mouseMovedThisFrame) {
                _ignoreNextMouseMovement = false;
            }
        } else {
            _deltaMousePos = _frameMousePos - newPos;
        }
        _frameMousePos = newPos;
        _mouseMovedThisFrame = false; //set to true in mouseCallback
    }

    vec2 getMousePos() {
        return _frameMousePos;
    }

    void updateTimeVariables() {
        double t = trueTime();
        _deltaTime = t - _frameTime;
        _frameTime = trueTime();
    }

    double trueTime() {
        return glfwGetTime() - _startupTime;
    }

    double frameTime() {
        return _frameTime;
    }

    double deltaTime() {
        return _deltaTime;
    }

    double fps() {
        return 1.0/_deltaTime;
    }

    ShaderProgram& getNullShader() {
        return *_nullShaderProgram;
    }



    void close() {
        glfwSetWindowShouldClose(_windowPtr, true);
    }

    void terminate() {
        glfwTerminate();
    }

    void loadInputs() {
        glfwPollEvents();
    }

    bool isHeld(Key key) {
        return (glfwGetKey(_windowPtr, (int) key) == GLFW_PRESS);
    }

    bool isPressed(Key key) {
        auto ind = (size_t)key;
        bool ret = false;
        bool held = isHeld(key);
        if (!_keyPressed[ind] && held) {
            ret = true;
        }
        _keyPressed[ind] = held;
        return ret;
    }

    void display() {
        glfwSwapBuffers(_windowPtr);

        updateTimeVariables();
        updateMouseVariables();

        _isFirstFrame = false;
    }

    vec2 getDeltaMousePos() {
        return _deltaMousePos;
    }

    void setMouseLocked(bool shouldLock) {
        if (shouldLock != _isMouseLocked) {
            _ignoreNextMouseMovement = true; // prevent any snapping of camera
            glfwSetCursorPos(_windowPtr, getWidth()/2, getHeight()/2);
        }
        int value = shouldLock? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;
        glfwSetInputMode(_windowPtr, GLFW_CURSOR, value);
        _isMouseLocked = shouldLock;
    }

    void toggleMouseLocked() {
        setMouseLocked(!_isMouseLocked);
    }

    bool mouseLocked() {
        return _isMouseLocked;
    }

    void setWireframe(bool displayWireframe) {
        int value = displayWireframe ? GL_LINE : GL_FILL;
        glPolygonMode(GL_FRONT_AND_BACK, value);
        _isWireframe = displayWireframe;
    }

    void toggleWireframe() {
        setWireframe(!_isWireframe);
    }

    bool wireFrame() {
        return _isWireframe;
    }

    double getFPS() {
        return 1.0 / deltaTime();
    }

    void capFPS(bool shouldCap) {
        glfwSwapInterval((int)shouldCap);
    }

    void registerObject(Object& obj) {
        _objectList.push_back(&obj);
    }
} // namespace slt::window
