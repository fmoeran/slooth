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

    Camera camera(45.0, {0, 0, 2});
    camera.setYaw(180);


    const int N = 1000;
    const int M = 10;
    std::vector<Cuboid> cubes(N);
    for (int i=0; i<N; i++) {
        auto x= (float)(i%M), y = (float)((i/M)%M), z = (float)((i/M/M)%M);
        x -= (float)M/2;
        y -= (float)M/2;
        z = -z;
        cubes[i].setWorldSpace({x, y, z});
        cubes[i].setPlainColour({0.8, 0.4, 0.6});
        cubes[i].setScale(vec3(0.5));
    }


//    PointLight light1({1, 1, 1});

    DirectionalLight light2({1, -1, 1});
    DirectionalLight light3({-1, -1, -1});


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

        camera.drawAll();

        window::display();

        std::cout << window::getFPS() << '\n';
    }
    window::terminate();
}