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
    glm::vec3 acceleration;
    float PLAYER_SPEED = 1.0f;

    if (Keyboard::getInstance().getKey(GLFW_KEY_W))
    {
        acceleration.x += -glm::cos(glm::radians(rotation.y + 90)) * PLAYER_SPEED;
        acceleration.z += -glm::sin(glm::radians(rotation.y + 90)) * PLAYER_SPEED;
    }
    if (Keyboard::getInstance().getKey(GLFW_KEY_S))
    {
        acceleration.x += glm::cos(glm::radians(rotation.y + 90)) * PLAYER_SPEED;
        acceleration.z += glm::sin(glm::radians(rotation.y + 90)) * PLAYER_SPEED;
    }

    velocity += acceleration;

    float xOffset = oldMouse.x - newMouse.x, yOffset = oldMouse.y - newMouse.y;
    xOffset *= 2.5f;
    yOffset *= 2.5f;

    rotation.y += xOffset;
    rotation.x += yOffset;

    if (rotation.y > 89.0f)
        rotation.y = 89.0f;
    if (rotation.y < -89.0f)
        rotation.y = -89.0f;
}

void Player::update()
{
    position += velocity * DeltaCounter::getInstance().delta;

    camera = calculateCameraMatrix(position, rotation, projection);
}

const glm::mat4 Player::getCameraMatrix() const
{
    return camera;
}

} // namespace entity
