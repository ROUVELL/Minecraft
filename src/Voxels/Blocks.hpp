#pragma once

#include <string>
#include <array>

#include "../vendors/json/json.hpp"
#include "../typedefs.hpp"
#include "../constants.hpp"

inline constexpr int TEXTURE_ARRAY_SIZE = 320;
inline constexpr int TEXTURE_FRAME_SIZE = 32;
inline constexpr float FRAME_UV_SIZE = ((float)TEXTURE_FRAME_SIZE / (float)TEXTURE_ARRAY_SIZE);

struct UVRegion
{
    float u1 = 0.0;
    float v1 = 0.0;
    float u2 = FRAME_UV_SIZE;
    float v2 = FRAME_UV_SIZE;

    UVRegion() = default;
    UVRegion(float u, float v)
    {
        u1 = u / TEXTURE_ARRAY_SIZE;
        v1 = v / TEXTURE_ARRAY_SIZE;

        u2 = u1 + FRAME_UV_SIZE;
        v2 = v1 + FRAME_UV_SIZE;
    }
};

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


class Blocks
{
    static std::array<Block, MAX_BLOCKS_COUNT> blocks;

    Blocks() = default;
    ~Blocks() = default;

    static void addBlock(const nlohmann::json& data);

public:
    static void initialize();

    static bool exists(voxel_t id);
    static uint64_t count();

    static const Block& getBlock(voxel_t id);
};