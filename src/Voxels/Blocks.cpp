#include "Blocks.hpp"

#include <fstream>
#include <unordered_map>
#include <istream>

#include "../vendors/json/json.hpp"

using json = nlohmann::json;

json loadJSON(const char* path);


std::unordered_map<voxel_t, Block> Blocks::blocks(256);

void Blocks::addBlock(voxel_t id, const std::string& name)
{
    if (!exists(id))
        blocks.emplace(id, Block{ name });
}

void Blocks::initialize()
{
    addBlock(0, "air");

    json data = loadJSON("../res/blocks.json");
    if (data.is_array())
    {
        for (auto& blockData : data)
            if (blockData.is_object())
                addBlock(blockData["id"], blockData["name"]);
    }
}

bool Blocks::exists(voxel_t id)
{
    return blocks.find(id) != blocks.end();
}

uint64_t Blocks::count()
{
    return blocks.size();
}

const Block& Blocks::getBlock(voxel_t id)
{
    if (exists(id))
        return blocks[id];
    return blocks[0];
}

json loadJSON(const char* path)
{
    std::ifstream file{ path };

    json data;

    if (file.is_open())
        data = json::parse(file);

    file.close();

    return data;
}