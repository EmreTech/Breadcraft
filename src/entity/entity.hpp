#pragma once

#include <utils/glm_include.hpp>

namespace entity
{
    
struct Entity
{
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 rotation;
};

} // namespace entity