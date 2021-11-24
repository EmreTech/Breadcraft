#include <window.hpp>
#include <gl/shader.hpp>
#include <gl/vertexArray.hpp>

#include <iostream>

gl::Shader shade;
gl::VertexArray va;
//unsigned int VAO, EBO;

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

    std::vector<unsigned int> indices {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };  

    /*
    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    */
	
	va.create();
    va.addVertexBuffer(3, vertices);
    va.addIndexBuffer(indices);

    /*
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    */
}

void render()
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

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
