#pragma once

#include <array>
#include <utils/glm_include.hpp>

namespace world
{

struct Chunk
{
    Chunk(glm::vec3 pos);

    void setBlock(unsigned short block, glm::vec3 pos);
    unsigned short getBlock(glm::vec3 pos);

    const glm::vec3 getChunkPos() const;

    std::array<unsigned short, 4096> blocks;

    private:
    glm::vec3 position;
};

} // namespace world
