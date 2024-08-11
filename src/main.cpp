#include "core/window.hpp"
#include "core/camera.hpp"
#include "objects/rect.hpp"
#include "objects/cuboid.hpp"

using namespace slt;

const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 600;


int main()
{
    window::init(SCR_WIDTH, SCR_HEIGHT, (char*)"Slooth Window");
    Camera camera(45.0, {0, 0, 2});
    camera.setYaw(180);


//    Rect robj(vec3(0, 0, 0), 1.0, 1.0);
//    rect.setPlainColour(255, 0, 0);

    Cuboid obj({0, 0, 0}, {5, 5, 1});
    obj.setPlainColour({1, 0, 0, 1});

    window::setMouseLocked(true);
//    window::toggleWireframe();

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

        camera.drawObject(obj);

        window::display();
    }

    window::terminate();
}