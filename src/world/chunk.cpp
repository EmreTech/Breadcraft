#include <world/chunk.hpp>

#include <utils/math.hpp>

namespace world
{

Chunk::Chunk(glm::vec3 pos) : position{pos}
{}

void Chunk::setBlock(unsigned short block, glm::vec3 pos)
{
    int i = positionToIndex(pos, 16);
    blocks[i] = block;
}

unsigned short Chunk::getBlock(glm::vec3 pos)
{
    int i = positionToIndex(pos, 16);
    return blocks[i];
}

const glm::vec3 Chunk::getChunkPos() const
{
    return position;
}

} // namespace world
