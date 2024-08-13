# Slooth

Very much a WIP. A **High and low level** C++ graphics API. With abstractions you might see in SDL or SFML 
but with the capability to design specific renderable objects and render pipelines.

<!--
## Program Hierarchy

![](images/Hierarchy.png)
-->

## Example Program

This is a quick program to create and display a cube on a plane with two lights.
The default camera methods allow the user to move around with WASD.

```c++

#include "core/window.hpp"
#include "core/camera.hpp"
#include "core/light.hpp"
#include "objects/cuboid.hpp"
#include "objects/plane.hpp"

using namespace slt;

const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    window::init(SCR_WIDTH, SCR_HEIGHT, (char*)"Slooth Window");
    Camera camera(45.0, {0, 0, 2});

    //         position   dimensions
    Cuboid obj({0, 0, 0}, {1, 1, 1});
    obj.setPlainColour({0.8, 0.3, 0.5});

    //            position     dimensions  vertexCounts
    Plane plane({0, -0.5, 0}, {100, 100}, {100, 100});

    //                 position
    PointLight light1({1, 1, 1});

    //                       direction
    DirectionalLight light2({1, -1, 1});

    window::setMouseLocked(true);

    while (!window::shouldClose()) {
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

        window::display();
    }
    window::terminate();
}
```

![](images/Example.png)

