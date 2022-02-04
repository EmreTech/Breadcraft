#include <utils/glm_include.hpp>
#include <math.h>

glm::vec3 localToGlobalPosition(const glm::vec3 pos, const glm::vec3 localChunkPos)
{
    return pos * localChunkPos;
}

glm::vec3 globalToLocalPosition(const glm::vec3 pos)
{
    pos.x %= 15;
    pos.y %= 15;
    pos.z %= 15;

    return pos;
}

int positionToIndex(const glm::vec3 pos, int size)
{
    float s = (float) size;
    return pos.y * s * s + pos.z * s + pos.x;
}