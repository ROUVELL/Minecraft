#pragma once

#include <string>

#include "../typedefs.hpp"

class Texture;

struct Color
{
    u8 r, g, b, a;

    Color() : r(255), g(255), b(255), a(255) { }
    Color(u8 scalar, u8 a = 255) : r(scalar), g(scalar), b(scalar), a(a) { }
    Color(u8 r, u8 g, u8 b, u8 a = 255) : r(r), g(g), b(b), a(a) { }
};

namespace colors
{
    const Color WHITE{ 255 };
    const Color BLACK{ 0 };
    const Color RED{ 255, 0, 0 };
    const Color GREEN{ 0, 255, 0 };
    const Color BLUE{ 0, 0, 255 };
    const Color TRANSPARENT{ 0, 0 };
}

class Image final
{
    u8* data;
    u32 width, height, channels;

public:
    Image();
    Image(const std::string& path);
    Image(u32 width, u32 height, u32 channels = 4);
    Image(const Image&);
    Image(Image&&) noexcept;
    ~Image();

    bool isRGB()  const { return channels == 3; }
    bool isRGBA() const { return channels == 4; }

    u32 getWidth()      const { return width; }
    u32 getHeight()     const { return height; }
    u32 getChannels()   const { return channels; }
    const u8* getData() const { return data; }

    /* If isRGB return true alpha will be ignored */
    void setPixel(u32 x, u32 y, Color color);
    void blit(u32 x, u32 y, const Image& img);
    
    Image subImage(u32 x, u32 y, u32 w, u32 h) const;
    Texture makeTexture() const; 

    Image copy() const;
    void del();

};