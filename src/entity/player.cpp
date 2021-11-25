#include <entity/player.hpp>

#include <utils/keyboard.hpp>
#include <utils/deltaCounter.hpp>

namespace
{

glm::mat4 calculateCameraMatrix(const glm::vec3 &pos, const glm::vec3 &rot, const glm::mat4 &proj)
{
    glm::mat4 view{1.0f};
    view = glm::rotate(view, glm::radians(rot.x), {1,0,0});
    view = glm::rotate(view, glm::radians(rot.y), {0,1,0});
    view = glm::rotate(view, glm::radians(rot.z), {0,0,1});
    view = glm::translate(view, -pos);
    
    return proj * view;
}

} // namespace


namespace entity
{

Player::Player()
{
    projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);
}

void Player::handleKeys(glm::vec2 oldMouse, glm::vec2 newMouse)
{
    glm::vec3 acceleration{0.0f};
    float PLAYER_SPEED = 1.0f;

    if (Keyboard::getInstance().getKey(GLFW_KEY_W) == GLFW_PRESS ||
    Keyboard::getInstance().getKey(GLFW_KEY_W) == GLFW_REPEAT)
    {
        acceleration.x += glm::cos(glm::radians(rotation.y + 90)) * PLAYER_SPEED;
        acceleration.z += glm::sin(glm::radians(rotation.y + 90)) * PLAYER_SPEED;
    }
    if (Keyboard::getInstance().getKey(GLFW_KEY_S) == GLFW_PRESS ||
    Keyboard::getInstance().getKey(GLFW_KEY_S) == GLFW_REPEAT)
    {
        acceleration.x -= glm::cos(glm::radians(rotation.y + 90)) * PLAYER_SPEED;
        acceleration.z -= glm::sin(glm::radians(rotation.y + 90)) * PLAYER_SPEED;
    }
    if (Keyboard::getInstance().getKey(GLFW_KEY_A) == GLFW_PRESS ||
    Keyboard::getInstance().getKey(GLFW_KEY_A) == GLFW_REPEAT)
    {
        acceleration.x -= glm::cos(glm::radians(rotation.y));
        acceleration.z -= glm::sin(glm::radians(rotation.y));
    }
    if (Keyboard::getInstance().getKey(GLFW_KEY_D) == GLFW_PRESS ||
    Keyboard::getInstance().getKey(GLFW_KEY_D) == GLFW_REPEAT)
    {
        acceleration.x += glm::cos(glm::radians(rotation.y));
        acceleration.z += glm::sin(glm::radians(rotation.y));
    }

    velocity += acceleration;

    float xOffset = oldMouse.x - newMouse.x, yOffset = oldMouse.y - newMouse.y;
    xOffset *= 1.5f;
    yOffset *= 1.5f;

    rotation.y += xOffset;
    rotation.x -= yOffset;

    if (rotation.x > 269.7f)
        rotation.x = 269.7f;
    if (rotation.x < 89.9f)
        rotation.x = 89.9f;
    
    if (rotation.y > 89.9f)
        rotation.y = 89.9f;
    if (rotation.y < -89.9f)
        rotation.y = -89.9f;
}

void Player::update()
{
    //position += velocity * DeltaCounter::getInstance().delta;
    position.x += velocity.x * DeltaCounter::getInstance().delta;
    position.y += velocity.y * DeltaCounter::getInstance().delta;
    position.z += velocity.z * DeltaCounter::getInstance().delta;

    velocity.x *= 0.9f;
    velocity.z *= 0.9f;

    camera = calculateCameraMatrix(position, rotation, projection);
}

const glm::mat4 Player::getCameraMatrix() const
{
    return camera;
}

} // namespace entity
