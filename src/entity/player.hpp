#pragma once

#include <entity/entity.hpp>

namespace entity
{

struct Player : Entity
{
    Player();
    Player(const glm::vec3 startPos);

    void handleKeys(glm::vec2 oldMouse, glm::vec2 newMouse);
    void update();

    const glm::mat4 getCameraMatrix() const;

    private:
    glm::mat4 projection{1.0f};
    // Camera = projection x view
    glm::mat4 camera{1.0f};
};

} // namespace entity