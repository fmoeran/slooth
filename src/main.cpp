#include "glad/glad.h"
#include "GLFW/glfw3.h"


#include "core/window.hpp"
#include "core/camera.hpp"
#include "core/vertex.hpp"
#include "core/object.hpp"
#include "objects/plane.hpp"

#include <iostream>

using namespace slt;


// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    window::init(SCR_WIDTH, SCR_HEIGHT, (char*)"Slooth Window");

    Camera camera(45.0, {0, 1, -10});

    Plane plane(10, 10, 1000, 1000);

    window::setMouseLocked(true);

    while (!window::shouldClose())
    {
        window::loadInputs();
        if (window::isPressed(Key::ESCAPE)) {
            window::toggleMouseLocked();
        }
        camera.pollDefaultMovementInputs();

        window::fill(0, 0, 0, 1);

        camera.drawObject(plane);

        window::display();
    }

    glfwTerminate();
    return 0;
}



