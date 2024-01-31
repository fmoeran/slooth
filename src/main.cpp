#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "window.hpp"
#include "camera.hpp"
#include "vertex.hpp"
#include "object.hpp"

#include <iostream>


void loadGlad();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

VertexColored vertices[] = {
        VertexColored(0.5, -0.5, 0, 1, 0, 0),
        VertexColored(0.0, 0.5, 0, 0, 1, 0),
        VertexColored(-0.5, -0.5, 0, 0, 0, 1)
};


unsigned int indices[] = {
        0, 1, 2,
};


int main()
{
    Window window(SCR_WIDTH, SCR_HEIGHT, (char*)"Slooth Window");

    Camera camera(window);

    loadGlad();

    Object obj;
    obj.setVertices(VertexEnum::VERTEX_COLORED, vertices, sizeof(vertices), indices, sizeof(indices));
    obj.setShaders();


    while (!window.shouldClose())
    {
        window.processInput();
        window.fill(0, 0, 0, 1);

        camera.drawObject(obj);

        window.display();
    }

    glfwTerminate();
    return 0;
}


void loadGlad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}
