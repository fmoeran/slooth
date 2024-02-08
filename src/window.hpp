//
// Created by felix on 02/09/2023.
//

#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace slt {
    class Window {
    public:
        Window(unsigned int width, unsigned int height, char *title = (char *) "Slooth Window");


        bool shouldClose();

        void processInput();

        void fill(float r, float g, float b, float a);

        void display();

        [[nodiscard]] unsigned int getHeight() const;

        [[nodiscard]] unsigned int getWidth() const;

        // returns the time since initialisation of the window
        [[nodiscard]] double time() const;

        // returns the time between initialisation and the last render of a frame
        [[nodiscard]] double frameTime() const;

        //  returns the time between the most recent frame render and the one before that
        [[nodiscard]] double deltaTime() const;

    private:
        GLFWwindow *window;
        unsigned int height, width;
        double _startupTime, _frameTime, _deltaTime;
    };
}
