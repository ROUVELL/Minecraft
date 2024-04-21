#include "Image.hpp"

#include <cstring>

#include "../vendors/stb/stb_image.hpp"
#include "Texture.hpp"


Image::Image()
    : width(0), height(0), channels(0)
{
    data = new uint8_t[1];
}

Image::Image(const std::string& path)
{
    data = stbi_load(path.c_str(), &width, &height, &channels, 0);
}

Image::Image(const Image& other)
    : width(other.width), height(other.height), channels(other.channels)
{
    data = new uint8_t[width * height * channels];
    memcpy(data, other.data, sizeof(uint8_t) * width * height * channels);
}

Image::Image(Image&& other) noexcept
    : data(other.data), width(other.width), height(other.height), channels(other.channels)
{
    other.data = nullptr;
    other.width = 0;
    other.height = 0;
    other.channels = 0;
}

Image::~Image()
{
    stbi_image_free(data);
}

// void Image::fill(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
// {
// }

void Image::setPixel(uint32_t x, uint32_t y, const Color color)
{
    if (isRGB())
    {
        uint32_t start = x * 3 + (y * width * 3);

        data[start++] = color. r;
        data[start++] = color.g;
        data[start] = color.b;
    }
    else if (isRGBA())
    {
       uint32_t start = x * 4 + (y * width * 4);

        data[start++] = color.r;
        data[start++] = color.g;
        data[start++] = color.b;
        data[start] = color.a;
    }
}

Texture Image::makeTexture() const
{
    return Texture(*this);
}

Image Image::copy() const
{
    return Image(*this);
}

void Image::del()
{
    stbi_image_free(data);
    data = nullptr;
    width = height = channels = 0;
}