#pragma once

#include <cstdint>
#include <string>

class Texture;

struct Color
{
    uint8_t r, g, b, a;

    Color() : r(255), g(255), b(255), a(255) { }
    Color(uint8_t scalar, uint8_t a = 255) : r(scalar), g(scalar), b(scalar), a(a) { }
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) : r(r), g(g), b(b), a(a) { }
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

class Image
{
    uint8_t* data;
    uint32_t width, height, channels;

public:
    Image();
    Image(const std::string& path);
    Image(uint32_t width, uint32_t height, uint32_t channels = 4);
    Image(const Image&);
    Image(Image&&) noexcept;
    ~Image();

    bool isRGB() const { return channels == 3; }
    bool isRGBA() const { return channels == 4; }

    uint32_t getWidth() const { return width; }
    uint32_t getHeight() const { return height; }
    uint32_t getChannels() const { return channels; }
    const uint8_t* getData() const { return data; }

    /* If isRGB return true alpha will be ignored */
    void setPixel(uint32_t x, uint32_t y, const Color color);

    void blit(uint32_t x, uint32_t y, const Image& img);

    Texture makeTexture() const; 

    Image copy() const;
    void del();

};