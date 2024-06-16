#pragma once

#include <unordered_map>
#include <string>

#include "../GL/Texture.hpp"
#include "../typedefs.hpp"


class Atlas final
{
    std::unordered_map<std::string, uv_region_t> regions;
    Texture textureArray;

public:
    Atlas();
    Atlas(const Atlas&) = delete;
    Atlas(Atlas&&) noexcept = delete;
    ~Atlas();

    uv_region_t getRegion(const std::string& name) const { return regions.at(name); }
    const Texture& getTexture() const { return textureArray; }
};

