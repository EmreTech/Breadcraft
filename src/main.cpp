#include <window.hpp>
#include <gl/shader.hpp>
#include <gl/vertexArray.hpp>
#include <gl/texture.hpp>
#include <utils/keyboard.hpp>
#include <utils/deltaCounter.hpp>
#include <entity/player.hpp>

#include <iostream>
#include <utils/glm_include.hpp>

gl::Shader shade;
gl::VertexArray va;
gl::Texture2D tex;

entity::Player player;

glm::vec2 lastPos, curPos;
bool firstMouse = true;

void processInput(GLFWwindow *window)
{
    if (Keyboard::getInstance().getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    curPos.x = xpos;
    curPos.y = ypos;

    if (firstMouse)
    {
        lastPos = curPos;
        firstMouse = false;
    }

    player.handleKeys(lastPos, curPos);

    lastPos = curPos;
}

void setup()
{
    glEnable(GL_DEPTH_TEST);

    shade.init("./res/shaders/basicVertex.glsl", "./res/shaders/basicFrag.glsl");

    std::vector<float> vertices {
        // Back
        1.0f, 1.0f, 0.0f,   // top right
        1.0f, 0.0f, 0.0f,   // bottom right
        0.0f, 0.0f, 0.0f,   // bottom left
        0.0f, 1.0f, 0.0f,   // top left

        // Front
        1.0f, 1.0f, 1.0f,   // top right
        1.0f, 0.0f, 1.0f,   // bottom right
        0.0f, 0.0f, 1.0f,   // bottom left
        0.0f, 1.0f, 1.0f,   // top left

        // Left
        0.0f, 1.0f, 1.0f,   // top right
        0.0f, 1.0f, 0.0f,   // bottom right
        0.0f, 0.0f, 0.0f,   // bottom left
        0.0f, 0.0f, 1.0f,   // top left

        // Right
        1.0f, 1.0f, 1.0f,   // top right
        1.0f, 1.0f, 0.0f,   // bottom right
        1.0f, 0.0f, 0.0f,   // bottom left
        1.0f, 0.0f, 1.0f,   // top left

        // Bottom
        1.0f, 0.0f, 1.0f,   // top right
        1.0f, 0.0f, 0.0f,   // bottom right
        0.0f, 0.0f, 0.0f,   // bottom left
        0.0f, 0.0f, 1.0f,   // top left

        // Top
        1.0f, 1.0f, 1.0f,   // top right
        1.0f, 1.0f, 0.0f,   // bottom right
        0.0f, 1.0f, 0.0f,   // bottom left
        0.0f, 1.0f, 1.0f,   // top left
    };

    std::vector<float> texCoords {
        // Back
        1.0f, 1.0f, // top right
        1.0f, 0.0f, // bottom right
        0.0f, 0.0f, // bottom left
        0.0f, 1.0f, // top left

        // Front
        1.0f, 1.0f, // top right
        1.0f, 0.0f, // bottom right
        0.0f, 0.0f, // bottom left
        0.0f, 1.0f, // top left

        // Left
        1.0f, 1.0f, // top right
        1.0f, 0.0f, // bottom right
        0.0f, 0.0f, // bottom left
        0.0f, 1.0f, // top left

        // Right
        1.0f, 1.0f, // top right
        1.0f, 0.0f, // bottom right
        0.0f, 0.0f, // bottom left
        0.0f, 1.0f, // top left

        // Bottom
        1.0f, 1.0f, // top right
        1.0f, 0.0f, // bottom right
        0.0f, 0.0f, // bottom left
        0.0f, 1.0f, // top left

        // Top
        1.0f, 1.0f, // top right
        1.0f, 0.0f, // bottom right
        0.0f, 0.0f, // bottom left
        0.0f, 1.0f, // top left
    };

    std::vector<unsigned int> indices;
    unsigned int iCount = 0;

    for (size_t i{0}; i < 6; i++)
    {
        indices.push_back(iCount);
        indices.push_back(iCount + 1);
        indices.push_back(iCount + 3);
        indices.push_back(iCount + 1);
        indices.push_back(iCount + 2);
        indices.push_back(iCount + 3);

        iCount += 4;
    }
	
	va.create();
    va.addVertexBuffer(3, vertices);
    va.addVertexBuffer(2, texCoords);
    va.addIndexBuffer(indices);

    tex.create();
    tex.loadImage("./res/textures/container.jpg");
}

void update()
{
    player.update();
}

std::vector<glm::vec3> boxPos {
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, -1.0f, 0.0f),
};

void render()
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    tex.bind();
    shade.use();

    shade.set("camera", player.getCameraMatrix());

    va.bind();
    for (int i = 0; i < 2; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, boxPos[i]);
        shade.set("model", model);

        va.draw();
    }
}

int main(void)
{
    if (!Window::init())
        return -1;
    
    setupCallbacks();

    setup();
    while (!glfwWindowShouldClose(Window::getWindow()))
    {
        DeltaCounter::getInstance().update();
        processInput(Window::getWindow());

        std::cout << "Player rotation: " <<
        "(" << player.rotation.x << "," << player.rotation.y << ")" << '\n';

        update();
        render();

        glfwPollEvents();
        glfwSwapBuffers(Window::getWindow());
    }

    glfwTerminate();
    return 0;
}
