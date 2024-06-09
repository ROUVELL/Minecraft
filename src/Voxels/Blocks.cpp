#include "Blocks.hpp"

#include <fstream>

using json = nlohmann::json;


json loadJSON(const char* path);


std::array<Block, MAX_BLOCKS_COUNT> Blocks::blocks;

void Blocks::addBlock(const nlohmann::json& data, const Atlas& atlas)
{
    static voxel_id id = 1;

    Block block;
    block.name = data["name"];

    const auto& texture = data["texture"];
    
    if (!data.contains("texture"))  // key do not exist
    {
        block.uv_regions.front =
        block.uv_regions.back =
        block.uv_regions.right =
        block.uv_regions.left =
        block.uv_regions.top =
        block.uv_regions.bottom = atlas.getRegion(data["name"]);
    }
    else if (texture.is_string())  // "texture_name"
    {
        block.uv_regions.front =
        block.uv_regions.back =
        block.uv_regions.right =
        block.uv_regions.left =
        block.uv_regions.top =
        block.uv_regions.bottom = atlas.getRegion(texture);
    }
    else if (texture.size() == 3)  // [top, sides, bottom]
    {
        block.uv_regions.front =
        block.uv_regions.back =
        block.uv_regions.right =
        block.uv_regions.left =   atlas.getRegion(texture[1]);
        block.uv_regions.top =    atlas.getRegion(texture[0]);
        block.uv_regions.bottom = atlas.getRegion(texture[2]);
    }
    else if (texture.size() == 6) // [front, back, right, left, top, bottom]
    {
        block.uv_regions.front =  atlas.getRegion(texture[0]);
        block.uv_regions.back =   atlas.getRegion(texture[1]);
        block.uv_regions.right =  atlas.getRegion(texture[2]);
        block.uv_regions.left =   atlas.getRegion(texture[3]);
        block.uv_regions.top =    atlas.getRegion(texture[4]);
        block.uv_regions.bottom = atlas.getRegion(texture[5]);
    }

    blocks[id] = block;
    ++id;
}

void Blocks::initialize(const Atlas& atlas)
{
    Block& air = blocks[0] = Block();
    air.name = "air";

    json data = loadJSON("../res/blocks.json");
    if (data.is_array())
    {
        for (auto& blockData : data)
            if (blockData.is_object())
                addBlock(blockData, atlas);
    }
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