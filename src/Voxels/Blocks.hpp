#pragma once

#include <array>

#include "Atlas.hpp"
#include "../vendors/json/json.hpp"
#include "../typedefs.hpp"
#include "../constants.hpp"


struct UVRegions
{
    UVRegion front, back, right, left, top, bottom;
};

struct Block
{
    std::string name;  // unigue string name (air, dirt, grass, ...)
    UVRegions uv_regions;

    Block() : name("empty") { }
};


class Blocks final
{
    static std::array<Block, MAX_BLOCKS_COUNT> blocks;

    Blocks() = default;
    ~Blocks() = default;

    static void addBlock(const nlohmann::json& data, const Atlas& atlas);

public:
    static void initialize(const Atlas& atlas);

    static bool exists(voxel_t id);
    static uint64_t count();

    static const Block& getBlock(voxel_t id);
};