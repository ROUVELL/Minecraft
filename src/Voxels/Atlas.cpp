#include "Atlas.hpp"

#include <cstdint>
#include <filesystem>

#include "../Graphics/Image.hpp"


inline constexpr int FRAME_SIZE = 32;
inline constexpr int TEXTURE_SIZE = 128;
inline constexpr float UV_SIZE = (float)FRAME_SIZE / (float)TEXTURE_SIZE;

namespace fs = std::filesystem;

Atlas::Atlas()
{
    regions["all"] = UVRegion{ };

    Image arrayImg{ TEXTURE_SIZE, TEXTURE_SIZE };

    uint32_t x = 0;
    uint32_t y = 0;

    for (const auto& entry : fs::directory_iterator("../res/textures"))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".png")
        {
            Image img(entry.path());

            arrayImg.blit(x, y, img);

            float u = x / (float)TEXTURE_SIZE;
            float v = y / (float)TEXTURE_SIZE;
            regions[entry.path().filename().stem()] = UVRegion{ u, v, u + UV_SIZE, v + UV_SIZE };

            x += FRAME_SIZE;
            if (x >= TEXTURE_SIZE)
            {
                y += FRAME_SIZE;
                x = 0;
            }
        }
    }

    textureArray.fromImage(arrayImg);
}

Atlas::~Atlas()
{
    textureArray.del();
}