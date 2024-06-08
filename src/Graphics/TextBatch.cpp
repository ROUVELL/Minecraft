#include "TextBatch.hpp"

#include "../Window/Window.hpp"
#include "../Loaders/AssetsLoader.hpp"

inline constexpr int FONT_IMG_WIDTH = 256;
inline constexpr int FONT_IMG_HEIGHT = 256;

inline constexpr int SYMBOL_WIDTH = 16;
inline constexpr int SYMBOL_HEIGHT = 16;
inline constexpr int SYMBOLS_IN_ROW = 16;

inline constexpr float SYMBOL_UV_WIDTH = (float)SYMBOL_WIDTH / (float)FONT_IMG_WIDTH;
inline constexpr float SYMBOL_UV_HEIGHT = (float)SYMBOL_HEIGHT / (float)FONT_IMG_HEIGHT;


TextBatch::TextBatch()
    : mesh({ 2, 2, 4 }),  // x, y,   u, v,   r, g, b, a
    index(0)
{
}

TextBatch::~TextBatch()
{
    mesh.del();
}

void TextBatch::text(const std::string& text, int x, int y, float r, float g, float b, float a)
{
    float sx = (x * 2.0) / Window::getWidth() - 1.0;
    float sy = 1.0 - (y * 2.0) / Window::getHeight();

    const float w = Window::getPixelWidth() * SYMBOL_WIDTH;
    const float h = Window::getPixelHeight() * SYMBOL_HEIGHT;

    for (unsigned i = 0; i < text.length(); ++i)
    {
        unsigned char c = text[i];

        if (c == '\t' || c == '\f' || c == '\r' || c == ' ')
        {
            sx += w / 2.0;
            continue;
        }
        if (c == '\n')
        {
            sx = (x * 2.0) / Window::getWidth() - 1.0;
            sy -= h;
            continue;
        }

        float u = (float)(c % SYMBOLS_IN_ROW) / SYMBOL_WIDTH;
        float v = (float)(c / SYMBOLS_IN_ROW) / SYMBOL_HEIGHT;

        meshData.vertices.insert(meshData.vertices.end(), { sx, sy, u, v, r, g, b, a });
        meshData.vertices.insert(meshData.vertices.end(), { sx + w, sy, u + SYMBOL_UV_WIDTH, v, r, g, b, a });
        meshData.vertices.insert(meshData.vertices.end(), { sx + w, sy - h, u + SYMBOL_UV_WIDTH, v + SYMBOL_UV_HEIGHT, r, g, b, a });
        meshData.vertices.insert(meshData.vertices.end(), { sx, sy - h, u, v + SYMBOL_UV_HEIGHT, r, g, b, a });

        meshData.indices.insert(meshData.indices.end(), { index, index + 1, index + 2, index, index + 2, index + 3 });
        index += 4;

        sx += w / 2.0;
    }
}

void TextBatch::render(AssetsLoader& assets)
{
    assets.getShader("text")->use();
    assets.getTexture("fonts/font")->bindUnit();

    mesh.build(meshData);
    mesh.render();

    meshData.vertices.clear();
    meshData.indices.clear();
    index = 0;
}