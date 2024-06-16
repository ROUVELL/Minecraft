#pragma once

#include <string>

#include "../typedefs.hpp"

class Texture;

class Image final
{
    u8* data = nullptr;

    u32 width = 0;
    u32 height = 0;
    u32 channels = 0;

public:
    Image() = default;
    Image(const std::string& path) noexcept;
    Image(u32 width, u32 height, u32 channels = 4) noexcept;
    Image(const Image&) noexcept;
    Image(Image&&) noexcept;
    ~Image() noexcept;

    bool isRGB()  const noexcept { return channels == 3; }
    bool isRGBA() const noexcept { return channels == 4; }

    u32 getWidth() const noexcept      { return width; }
    u32 getHeight() const noexcept     { return height; }
    u32 getChannels() const noexcept   { return channels; }
    const u8* getData() const noexcept { return data; }

    /* If isRGB return true alpha will be ignored */
    void setPixel(u32 x, u32 y, color_t color) noexcept;
    void blit(u32 x, u32 y, const Image& img) noexcept;
    
    Image subImage(u32 x, u32 y, u32 w, u32 h) const noexcept;
    Texture makeTexture() const noexcept; 

    Image copy() const noexcept;
    void del() noexcept;
};