#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vertex.hpp"
#include "shader.hpp"

#include <iostream>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
GLFWwindow* createWindow(unsigned int width, unsigned int height, char* title);
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
    GLFWwindow* window = createWindow(SCR_WIDTH, SCR_HEIGHT, (char*)"GLFW window");

    loadGlad();

    Shader vert = Shader("../src/shaders/default.vert", ShaderType::VERT);
    Shader frag = Shader("../src/shaders/default.frag", ShaderType::FRAG);
    ShaderProgram program;
    program.addShader(vert);
    program.addShader(frag);
    program.buildProgram();


    VertexArray object(vertices, sizeof(vertices), indices, sizeof(indices), VertexEnum::VERTEX_COLORED);


    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        program.use();
        object.draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}



GLFWwindow* createWindow(unsigned int width, unsigned int height, char* title){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if defined(__APPLE__)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    return window;
}

void loadGlad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}