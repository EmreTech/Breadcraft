#include <window.hpp>
#include <gl/shader.hpp>
#include <gl/vertexArray.hpp>
#include <gl/texture.hpp>

#include <iostream>

gl::Shader shade;
gl::VertexArray va;
gl::Texture2D tex;

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void setup()
{
    shade.init("./res/shaders/basicVertex.glsl", "./res/shaders/basicFrag.glsl");

    std::vector<float> vertices {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    std::vector<float> texCoords {
        1.0f, 1.0f, // top right
        1.0f, 0.0f, // bottom right
        0.0f, 0.0f, // bottom left
        0.0f, 1.0f, // top left
    };

    std::vector<unsigned int> indices {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
	
	va.create();
    va.addVertexBuffer(3, vertices);
    va.addVertexBuffer(2, texCoords);
    va.addIndexBuffer(indices);

    tex.create();
    tex.loadImage("./res/textures/container.jpg");
}

void render()
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    tex.bind();
    shade.use();
    va.bind();
    va.draw();
}

int main(void)
{
    if (!Window::init())
        return -1;
    else
        setupCallbacks();

    setup();
    while (!glfwWindowShouldClose(Window::getWindow()))
    {
        processInput(Window::getWindow());

        render();

        glfwPollEvents();
        glfwSwapBuffers(Window::getWindow());
    }

    glfwTerminate();
    return 0;
}
