#include <utils/glm_include.hpp>
#include <math.h>

glm::vec3 localToGlobalPosition(const glm::vec3 pos, const glm::vec3 localChunkPos)
{
    return pos * localChunkPos;
}

glm::vec3 globalToLocalPosition(const glm::vec3 pos)
{
    glm::vec3 output{0.0f};
    output.x = glm::mod(pos.x, 16.0f);
    output.y = glm::mod(pos.y, 16.0f);
    output.z = glm::mod(pos.z, 16.0f);

    return output;
}

int positionToIndex(const glm::vec3 pos, int size)
{
    float s = (float) size;
    return pos.y * pow(s, 2) + pos.z * s + pos.x;
}