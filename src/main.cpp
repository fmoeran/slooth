#include "core/window.hpp"
#include "core/camera.hpp"
#include "core/light.hpp"
#include "objects/rect.hpp"
#include "objects/cuboid.hpp"
#include "objects/plane.hpp"

using namespace slt;

const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    window::init(SCR_WIDTH, SCR_HEIGHT, (char*)"Slooth Window");
    Camera camera(45.0, {0, 0, 2});
    camera.setYaw(180);

    Cuboid obj({0, 0, 0}, {1, 1, 1});
    obj.setPlainColour({0.8, 0.3, 0.5});

    Rect rect({0, 0, 1}, 1, 1);

    Plane plane({0, -0.5, 0}, {100, 100}, {100, 100});

    PointLight light1({1, 1, 1});

    PointLight light2({-1, 1, 10});

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
        camera.drawObject(rect);
        camera.drawObject(plane);

        window::display();
    }
    window::terminate();
}