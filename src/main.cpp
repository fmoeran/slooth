#include "core/window.hpp"
#include "core/camera.hpp"
#include "objects/rect.hpp"

using namespace slt;

const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 600;


int main()
{
    window::init(SCR_WIDTH, SCR_HEIGHT, (char*)"Slooth Window");

    Camera camera(45.0, {0, 1, -6});

    Rect rect(vec3(0, 0, 0), 1.0, 1.0);

//    window::toggleWireframe();
    window::setMouseLocked(true);

    while (!window::shouldClose())
    {
        // Input checking to unlock the cursor
        window::loadInputs();
        if (window::isPressed(Key::ESCAPE)) {
            window::toggleMouseLocked();
        }

        // Camera movement
        camera.pollDefaultMovementInputs();

        // Displaying object
        window::fill(0, 0, 0, 1);


        camera.drawObject(rect);

        window::display();
    }

    window::terminate();
}