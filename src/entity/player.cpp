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

    /*
    glm::vec3 calculated_pos = glm::vec3(pos.x, 0.0f, pos.z);
    glm::vec3 target_pos = glm::vec3(0.0f);
    glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    glm::vec3 zaxis = glm::normalize(calculated_pos - target_pos);
    glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(world_up), zaxis));
    glm::vec3 yaxis = glm::cross(zaxis, xaxis);

    glm::mat4 translation = glm::mat4(1.0f);
    translation[3][0] = -calculated_pos.x;
    translation[3][1] = -calculated_pos.y;
    translation[3][2] = -calculated_pos.z;
    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0][0] = xaxis.x;
    rotation[1][0] = xaxis.y;
    rotation[2][0] = xaxis.z;
    rotation[0][1] = yaxis.x;
    rotation[1][1] = yaxis.y;
    rotation[2][1] = yaxis.z;
    rotation[0][2] = zaxis.x;
    rotation[1][2] = zaxis.y;
    rotation[2][2] = zaxis.z; 

    glm::mat4 view = rotation * translation;
    return proj * view;
    */
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
        acceleration.x -= glm::cos(glm::radians(rotation.y + 90)) * PLAYER_SPEED;
        acceleration.z -= glm::sin(glm::radians(rotation.y + 90)) * PLAYER_SPEED;
    }
    if (Keyboard::getInstance().getKey(GLFW_KEY_S) == GLFW_PRESS ||
    Keyboard::getInstance().getKey(GLFW_KEY_S) == GLFW_REPEAT)
    {
        acceleration.x += glm::cos(glm::radians(rotation.y + 90)) * PLAYER_SPEED;
        acceleration.z += glm::sin(glm::radians(rotation.y + 90)) * PLAYER_SPEED;
    }
    if (Keyboard::getInstance().getKey(GLFW_KEY_A) == GLFW_PRESS ||
    Keyboard::getInstance().getKey(GLFW_KEY_A) == GLFW_REPEAT)
    {
        acceleration.x -= glm::cos(glm::radians(rotation.y)) * PLAYER_SPEED;
        acceleration.z -= glm::sin(glm::radians(rotation.y)) * PLAYER_SPEED;
    }
    if (Keyboard::getInstance().getKey(GLFW_KEY_D) == GLFW_PRESS ||
    Keyboard::getInstance().getKey(GLFW_KEY_D) == GLFW_REPEAT)
    {
        acceleration.x += glm::cos(glm::radians(rotation.y)) * PLAYER_SPEED;
        acceleration.z += glm::sin(glm::radians(rotation.y)) * PLAYER_SPEED;
    }
    if (Keyboard::getInstance().getKey(GLFW_KEY_SPACE) == GLFW_PRESS ||
    Keyboard::getInstance().getKey(GLFW_KEY_SPACE) == GLFW_REPEAT)
    {
        acceleration.y += PLAYER_SPEED;
    }
    if (Keyboard::getInstance().getKey(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
    Keyboard::getInstance().getKey(GLFW_KEY_LEFT_SHIFT) == GLFW_REPEAT)
    {
        acceleration.y -= PLAYER_SPEED;
    }

    velocity += acceleration;

    float xOffset = oldMouse.x - newMouse.x, yOffset = oldMouse.y - newMouse.y;
    xOffset *= 1.25f;
    yOffset *= 1.25f;

    rotation.y += xOffset;
    rotation.x -= yOffset;

    if (rotation.x > 89.0f)
        rotation.x = 89.0f;
    if (rotation.x < -89.0f)
        rotation.x = -89.0f;
}

void Player::update()
{
    //position += velocity * DeltaCounter::getInstance().delta;
    position.x += velocity.x * DeltaCounter::getInstance().delta;
    position.y += velocity.y * DeltaCounter::getInstance().delta;
    position.z += velocity.z * DeltaCounter::getInstance().delta;

    velocity.x *= 0.9f;
    velocity.y *= 0.9f;
    velocity.z *= 0.9f;

    camera = calculateCameraMatrix(position, rotation, projection);
}

const glm::mat4 Player::getCameraMatrix() const
{
    return camera;
}

} // namespace entity
