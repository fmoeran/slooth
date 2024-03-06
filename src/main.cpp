#include "core/window.hpp"
#include "core/camera.hpp"
#include "objects/plane.hpp"

using namespace slt;

const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 600;

//
//const VertexTexture verts[] = {
//        VertexTexture({0, 0, 0}, {0, 0}),
//        VertexTexture({1, 0, 0}, {1, 0}),
//        VertexTexture({0, 1, 0}, {0, 1}),
//        VertexTexture({1, 1, 0}, {1, 1}),
//};

const VertexPlain verts[] = {
        VertexPlain(0, 0, 0),
        VertexPlain(1, 0, 0),
        VertexPlain(0, 1, 0),
        VertexPlain(1, 1, 0),
};

const unsigned int inds[] = {
        0, 3, 1,
        0, 3, 2,
};


int main()
{
    window::init(SCR_WIDTH, SCR_HEIGHT, (char*)"Slooth Window");

    Camera camera(45.0, {0, 1, -1});

//    Plane plane(10, 10, 1000, 1000);

    Object obj;
    obj.setVertices(VertexEnum::VERTEX_PLAIN, (void*)verts, sizeof(verts), (void*)inds, sizeof(inds));
    obj.setShaders();

//    window::toggleWireframe();
    window::setMouseLocked(true);

    while (!window::shouldClose())
    {
        // Input checking to unlock the cursor
        window::loadInputs();
        if (window::isPressed(Key::ESCAPE)) {
            window::toggleMouseLocked();
        }

//        obj.setPlainColour(vec4(sin(((float)window::frameTime()) + 1) / 2));

        // Camera movement
        camera.pollDefaultMovementInputs();

        // Displaying object
        window::fill(0, 0, 0, 1);

//        camera.drawObject(plane);#
        camera.drawObject(obj);

        window::display();
    }

    window::terminate();
}
