#include "Blocks.hpp"

#include <unordered_map>

std::unordered_map<voxel_t, Block> Blocks::blocks(256);

void Blocks::addBlock(voxel_t id, const char* name)
{
    if (!exists(id))
        blocks.emplace(id, Block{ id, name });
}

void Blocks::initialize()
{
    addBlock(0, "air");
    addBlock(1, "grass");
}

bool Blocks::exists(voxel_t id)
{
    return blocks.find(id) != blocks.end();
}

const Block& Blocks::getBlock(voxel_t id)
{
    if (exists(id))
        return blocks[id];
    return blocks[0];
}