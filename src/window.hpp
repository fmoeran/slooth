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

        unsigned int getHeight() const;

        unsigned int getWidth() const;


    private:
        GLFWwindow *window;
        unsigned int height, width;
    };
}
