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
{
    VAO.setAttrData(0, 2, 0);
    VAO.setAttrData(1, 2, 2 * sizeof(float));
    VAO.setAttrData(2, 4, 4 * sizeof(float));

    VBO.create(nullptr, TEXT_BATCH_CAPICITY * sizeof(char_vertex_t), buffer_usage::DYNAMIC_DRAW);

    VAO.bindVBO(VBO.getID(), 8 * sizeof(float));

}

TextBatch::~TextBatch()
{
    VAO.del();
    VBO.del();
    count = 0;
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

        indices[count++] = index;
        indices[count++] = index + 1;
        indices[count++] = index + 2;
        indices[count++] = index;
        indices[count++] = index + 2;
        indices[count++] = index + 3;

        vertices[index++] = { sx, sy, u, v, r, g, b, a };
        vertices[index++] = { sx + w, sy, u + SYMBOL_UV_WIDTH, v, r, g, b, a };
        vertices[index++] = { sx + w, sy - h, u + SYMBOL_UV_WIDTH, v + SYMBOL_UV_HEIGHT, r, g, b, a };
        vertices[index++] = { sx, sy - h, u, v + SYMBOL_UV_HEIGHT, r, g, b, a };


        sx += w / 2.0;
    }
}

void TextBatch::render(AssetsLoader& assets)
{
    assets.getShader("text")->use();
    assets.getTexture("fonts/font")->bindUnit();

    VBO.write(vertices, index * sizeof(char_vertex_t));

    VAO.bind();
    VAO.drawElements(count, indices);
    VAO.unbind();

    count = 0;
    index = 0;
}