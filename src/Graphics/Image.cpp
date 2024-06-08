#include "Image.hpp"

#include <cstring>

#include "../vendors/stb/stb_image.hpp"
#include "../math.hpp"
#include "Texture.hpp"


Image::Image()
    : data(nullptr), width(0), height(0), channels(0)
{
}

Image::Image(const std::string& path)
{
    data = stbi_load(path.c_str(), (i32*)&width, (i32*)&height, (i32*)&channels, 0);
}

Image::Image(u32 width, u32 height, u32 channels)
    : width(width), height(height), channels(channels)
{
    data = new u8[width * height * channels];
    memset(data, 255, width * height * channels);
}

Image::Image(const Image& other)
    : width(other.width), height(other.height), channels(other.channels)
{
    data = new u8[width * height * channels];
    memcpy(data, other.data, width * height * channels);
}

Image::Image(Image&& other) noexcept
    : data(other.data), width(other.width), height(other.height), channels(other.channels)
{
    other.data = nullptr;
    other.width = other.height = other.channels = 0;
}

Image::~Image()
{
    del();
}

void Image::setPixel(u32 x, u32 y, Color color)
{
    u32 start = x * channels + y * width * channels;

    data[start++] = color.r;
    data[start++] = color.g;
    data[start++] = color.b;

    if (isRGBA())
        data[start] = color.a;
}

void Image::blit(u32 x, u32 y, const Image& img)
{
    if (x >= width || y >= height)
        return;

    if (isRGBA() && img.isRGB())
        return;

    for (u32 localX = 0; localX < min(width - x, img.width); ++localX)
        for (u32 localY = 0; localY < min(height - y, img.height); ++localY)
            {
                u32 srcIndex = localX * img.getChannels() + localY * img.getWidth() * img.getChannels();
                u32 dstIndex = (x + localX) * channels + (y + localY) * width * channels;
                
                data[dstIndex] = img.data[srcIndex];
                data[dstIndex + 1] = img.data[srcIndex + 1];
                data[dstIndex + 2] = img.data[srcIndex + 2];

                if (isRGBA())
                    data[dstIndex + 3] = img.data[srcIndex + 3];
            }
}


Image Image::subImage(u32 x, u32 y, u32 w, u32 h) const
{
    Image sub(w, h, channels);

    for (u32 localX = 0; localX < min(w, width - x); ++localX)
        for (u32 localY = 0; localY < min( h, height - y); ++localY)
        {
            u32 srcIndex = (localX + x) * channels + (localY + y) * width * channels;
            u32 dstIndex = localX * channels + localY * w * channels;
            
            sub.data[dstIndex] = data[srcIndex];
            sub.data[dstIndex + 1] = data[srcIndex + 1];
            sub.data[dstIndex + 2] = data[srcIndex + 2];

            if (isRGBA())
                sub.data[dstIndex + 3] = data[srcIndex + 3];
        }

    return sub;
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