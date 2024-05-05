#pragma once

#include <unordered_map>
#include <string>

#include "../Graphics/Texture.hpp"

struct UVRegion
{
    float u1 = 0.0;
    float v1 = 0.0;
    float u2 = 1.0;
    float v2 = 1.0;
};

class Atlas final
{
    std::unordered_map<std::string, UVRegion> regions;
    Texture textureArray;

public:
    Atlas();
    Atlas(const Atlas&) = delete;
    Atlas(Atlas&&) noexcept = delete;
    ~Atlas();

    UVRegion getRegion(const std::string& name) const { return regions.at(name); }
    const Texture& getTexture() const { return textureArray; }
};

