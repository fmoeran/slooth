//
// Created by felix on 02/09/2023.
//
#include "window.hpp"


#include "GLFW/glfw3.h"
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace slt {


    void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }

    Window::Window(unsigned int width, unsigned int height, char *title)
            : width(width), height(height) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if defined(__APPLE__)
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        // glfw window creation
        // --------------------
        window = glfwCreateWindow(width, height, title, nullptr, nullptr);

        if (window == nullptr) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            throw;
        }

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);



        _startupTime = glfwGetTime();
    }

    void Window::processInput() {
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    unsigned int Window::getHeight() const {
        return height;
    }

    unsigned int Window::getWidth() const {
        return width;
    }

    bool Window::shouldClose() {
        return glfwWindowShouldClose(window);
    }

    void Window::fill(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::display() {
        glfwSwapBuffers(window);

        // update time variables
        double t = time();
        _deltaTime = t - _frameTime;
        _frameTime = time();
    }

    double Window::time() const {
        return glfwGetTime() - _startupTime;
    }

    double Window::frameTime() const{
        return _frameTime;
    }

    double Window::deltaTime() const{
        return _deltaTime;
    }


}



