#include <window.hpp>
#include <gl/shader.hpp>
#include <gl/vertex_array.hpp>
#include <gl/texture.hpp>
#include <utils/keyboard.hpp>
#include <utils/delta_counter.hpp>
#include <entity/player.hpp>

#include <iostream>
#include <chrono>
#include <utils/glm_include.hpp>

gl::Shader shade;
gl::VertexArray va;
gl::Texture2D tex;
std::vector<glm::vec3> boxPos;

entity::Player player{glm::vec3(0.0f, 0.0f, 0.0f)};

glm::vec2 lastPos, curPos;
bool firstMouse = true;

bool wireframe = false;
std::chrono::time_point<std::chrono::steady_clock> lastWireframeTime;

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

    if (
        Keyboard::getInstance().getKey(GLFW_KEY_Q) == GLFW_PRESS &&
        (std::chrono::steady_clock::now() - lastWireframeTime).count() > 3e+9
    )
    {
        wireframe = !wireframe;
        lastWireframeTime = std::chrono::steady_clock::now();
    }

    player.handleKeys(lastPos, curPos);

    lastPos = curPos;
}

void setup()
{
    glEnable(GL_DEPTH_TEST);

    shade.init("./res/shaders/basicVertex.glsl", "./res/shaders/basicFrag.glsl");

    std::vector<float> vertices {
        // back face
        0.0f, 0.0f, 0.0f, // bottom-left
        1.0f, 0.0f, 0.0f, // bottom-right
        1.0f, 1.0f, 0.0f, // top-right
        0.0f, 1.0f, 0.0f, // top-left

        // front face
        0.0f, 0.0f, 1.0f, // bottom-left
        1.0f, 0.0f, 1.0f, // bottom-right
        1.0f, 1.0f, 1.0f, // top-right
        0.0f, 1.0f, 1.0f, // top-left

        // left face
        0.0f, 0.0f, 0.0f, // bottom-left
        0.0f, 0.0f, 1.0f, // bottom-right
        0.0f, 1.0f, 1.0f, // top-right
        0.0f, 1.0f, 0.0f, // top-left

        // right face
        1.0f, 0.0f, 0.0f, // bottom-left
        1.0f, 0.0f, 1.0f, // bottom-right
        1.0f, 1.0f, 1.0f, // top-right
        1.0f, 1.0f, 0.0f, // top-left

        // bottom face
        0.0f, 0.0f, 1.0f, // bottom-left
        1.0f, 0.0f, 1.0f, // bottom-right
        1.0f, 0.0f, 0.0f, // top-right
        0.0f, 0.0f, 0.0f, // top-left

        // top face
        0.0f, 1.0f, 1.0f, // bottom-left
        1.0f, 1.0f, 1.0f, // bottom-right
        1.0f, 1.0f, 0.0f, // top-right
        0.0f, 1.0f, 0.0f, // top-left
    };

    std::vector<float> texCoords {
        // back face
        0.0f, 0.0f, // bottom-left
        1.0f, 0.0f, // bottom-right
        1.0f, 1.0f, // top-right
        0.0f, 1.0f, // top-left

        // front face
        0.0f, 0.0f, // bottom-left
        1.0f, 0.0f, // bottom-right
        1.0f, 1.0f, // top-right
        0.0f, 1.0f, // top-left

        // left face
        0.0f, 0.0f, // bottom-left
        1.0f, 0.0f, // bottom-right
        1.0f, 1.0f, // top-right
        0.0f, 1.0f, // top-left

        // right face
        0.0f, 0.0f, // bottom-left
        1.0f, 0.0f, // bottom-right
        1.0f, 1.0f, // top-right
        0.0f, 1.0f, // top-left

        // bottom face
        0.0f, 0.0f, // bottom-left
        1.0f, 0.0f, // bottom-right
        1.0f, 1.0f, // top-right
        0.0f, 1.0f, // top-left

        // top face
        0.0f, 0.0f, // bottom-left
        1.0f, 0.0f, // bottom-right
        1.0f, 1.0f, // top-right
        0.0f, 1.0f, // top-left
    };

    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 3; x++)
            for (int z = 0; z < 3; z++)
                boxPos.push_back(glm::vec3(x,y,z));
            
    std::vector<unsigned int> indices;
    unsigned int iCount = 0;

    for (size_t i{0}; i < 6; i++)
    {
        indices.push_back(iCount + 0);
        indices.push_back(iCount + 1);
        indices.push_back(iCount + 2);
        indices.push_back(iCount + 2);
        indices.push_back(iCount + 3);
        indices.push_back(iCount + 0);

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

void render()
{
    glClearColor(0.0f, 0.0f, 0.8417f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    tex.bind();
    shade.use();

    shade.set("camera", player.getCameraMatrix());

    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    va.bind();
    for (size_t i = 0; i < boxPos.size(); i++)
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

        std::cout << "Player position: " <<
        "(" << player.position.x << ", " << player.position.y << ")" << '\n';
        std::cout << "Player rotation: " <<
        "(" << player.rotation.x << ", " << player.rotation.y << ")" << '\n';

        update();
        render();

        glfwPollEvents();
        glfwSwapBuffers(Window::getWindow());
    }

    glfwTerminate();
    return 0;
}
