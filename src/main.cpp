#include "core/window.hpp"
#include "core/camera.hpp"
#include "core/light.hpp"
#include "objects/cuboid.hpp"
#include "objects/plane.hpp"
#include "objects/sphere.hpp"

using namespace slt;

const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    window::init(SCR_WIDTH, SCR_HEIGHT, (char*)"Slooth Window");

    window::capFPS(30);

    Camera camera(45.0, {0, 0, 2});
    camera.setYaw(180);

    Cuboid obj({0, 0, 0}, {1, 1, 1});
    obj.setPlainColour({0.8, 0.3, 0.5});

    UVSphere sphere({-1, 1, -1}, 1, 100);
    sphere.setPlainColour({0.4, 0.8, 0.6});

    Plane plane({0, -0.5, 0}, {100, 100}, {100, 100});

    PointLight light1({1, 1, 1});

    DirectionalLight light2({1, -1, 1});

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
        camera.drawObject(plane);
        camera.drawObject(sphere);

        window::display();
    }
    window::terminate();
}