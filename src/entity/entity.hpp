#pragma once

#include <utils/glm_include.hpp>

namespace entity
{
    
struct Entity
{
    glm::vec3 position{0.0f};
    glm::vec3 velocity{0.0f};
    glm::vec3 rotation{0.0f};
};

} // namespace entity