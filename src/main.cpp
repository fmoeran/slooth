#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "window.hpp"
#include "camera.hpp"
#include "vertex.hpp"
#include "object.hpp"

#include <iostream>

using namespace slt;


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//VertexColored vertices[] = {
//        VertexColored(0.5, -0.5, 0, 1, 0, 0),
//        VertexColored(0.0, 0.5, 0, 0, 1, 0),
//        VertexColored(-0.5, -0.5, 0, 0, 0, 1)
//};

Vertex vertices[] = {
        Vertex(0.5, -0.5, 0),
        Vertex(0.0, 0.5, 0),
        Vertex(-0.5, -0.5, 0)
};

unsigned int indices[] = {
        0, 1, 2,
};


int main()
{
    window::init(SCR_WIDTH, SCR_HEIGHT, (char*)"Slooth Window");

    Camera camera(45.0, {0, 0, -5});

    Object obj;
    obj.setVertices(VertexEnum::VERTEX, vertices, sizeof(vertices), indices, sizeof(indices));
    obj.setShaders();


    while (!window::shouldClose())
    {
        window::loadInputs();
        if (window::isPressed(Key::ESCAPE)) {
            std::cout << "HI" << std::endl;
            window::close();
        }

        camera.pollDefaultMovementInputs();

        window::fill(0, 0, 0, 1);

        camera.drawObject(obj);

        window::display();
    }

    glfwTerminate();
    return 0;
}



