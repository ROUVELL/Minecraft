#include "Blocks.hpp"

#include <fstream>

using json = nlohmann::json;


json loadJSON(const char* path);


std::array<Block, MAX_BLOCKS_COUNT> Blocks::blocks;

void Blocks::addBlock(const nlohmann::json& data)
{
    static voxel_t id = 1;

    Block block;
    block.name = data["name"];

    const auto& uv_data = data["uv"];
    if (uv_data.size() == 2)  // [u, v]
    {
        block.uv_regions.front =
        block.uv_regions.back =
        block.uv_regions.right =
        block.uv_regions.left =
        block.uv_regions.top =
        block.uv_regions.bottom = { uv_data[0], uv_data[1] };
    }
    else if (uv_data.size() == 3)  // [top, sides, bottom]
    {
        block.uv_regions.front =
        block.uv_regions.back =
        block.uv_regions.right =
        block.uv_regions.left =   { uv_data[1][0], uv_data[1][1] };
        block.uv_regions.top =    { uv_data[0][0], uv_data[0][1] };
        block.uv_regions.bottom = { uv_data[2][0], uv_data[2][1] };
    }
    else if (uv_data.size() == 6) // [front, back, right, left, top, bottom]
    {
        block.uv_regions.front =  { uv_data[0][0], uv_data[0][1] };
        block.uv_regions.back =   { uv_data[1][0], uv_data[1][1] };
        block.uv_regions.right =  { uv_data[2][0], uv_data[2][1] };
        block.uv_regions.left =   { uv_data[3][0], uv_data[3][1] };
        block.uv_regions.top =    { uv_data[4][0], uv_data[4][1] };
        block.uv_regions.bottom = { uv_data[5][0], uv_data[5][1] };
    }

    blocks[id] = block;
    ++id;
}

void Blocks::initialize()
{
    Block& air = blocks[0] = Block();
    air.name = "air";

    json data = loadJSON("../res/blocks.json");
    if (data.is_array())
    {
        for (auto& blockData : data)
            if (blockData.is_object())
                addBlock(blockData);
    }
}

bool Blocks::exists(voxel_t id)
{
    return id < count();
}

uint64_t Blocks::count()
{
    return blocks.size();
}

const Block& Blocks::getBlock(voxel_t id)
{
    return blocks[id];
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