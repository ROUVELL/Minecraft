#include "UIBatch.hpp"

#include "../Window/Window.hpp"
#include "../Loaders/AssetsLoader.hpp"


inline constexpr int FONT_IMG_WIDTH = 256;
inline constexpr int FONT_IMG_HEIGHT = 256;

inline constexpr int SYMBOL_WIDTH = 16;
inline constexpr int SYMBOL_HEIGHT = 16;
inline constexpr int SYMBOLS_IN_ROW = 16;

inline constexpr float SYMBOL_UV_WIDTH = (float)SYMBOL_WIDTH / (float)FONT_IMG_WIDTH;
inline constexpr float SYMBOL_UV_HEIGHT = (float)SYMBOL_HEIGHT / (float)FONT_IMG_HEIGHT;


UIBatch::UIBatch()
    : lines(UI_BATCH_LINES_CAPICITY * 2),
    sprites(UI_BATCH_SPRITES_CAPICITY * 4),
    spriteIndices(UI_BATCH_SPRITES_CAPICITY * 6)
{
    VAO.setAttrData(0, 2, 0);
    VAO.setAttrData(1, 2, 2 * sizeof(float));
    VAO.setAttrData(2, 4, 4 * sizeof(float));

    VBO.create(nullptr, (UI_BATCH_LINES_CAPICITY + UI_BATCH_SPRITES_CAPICITY * 4)* sizeof(ui_vertex_t), buffer_usage::STREAM_DRAW);

    VAO.bindVBO(VBO.getID(), sizeof(ui_vertex_t));

}

UIBatch::~UIBatch()
{
    VAO.del();
    VBO.del();
}

void UIBatch::sprite(int x, int y, int w, int h, uv_region_t uvregion, fcolor_t color)
{
    const float sx = (x * 2.0f) / Window::getWidth() - 1.0f;
    const float sy = 1.0f - (y * 2.0f) / Window::getHeight();

    const float sw = Window::getPixelWidth() * w;
    const float sh = Window::getPixelHeight() * h;

    u32 count = sprites.size();

    spriteIndices.push_back(count);
    spriteIndices.push_back(count + 1);
    spriteIndices.push_back(count + 2);
    spriteIndices.push_back(count);
    spriteIndices.push_back(count + 2);
    spriteIndices.push_back(count + 3);

    sprites.emplace_back( sx, sy, uvregion.u1, uvregion.v1, color );
    sprites.emplace_back( sx + sw, sy, uvregion.u2, uvregion.v1, color );
    sprites.emplace_back( sx + sw, sy - sh, uvregion.u2, uvregion.v2, color );
    sprites.emplace_back( sx, sy - sh, uvregion.u1, uvregion.v2, color );
}


void UIBatch::text(const std::string& text, int x, int y, fcolor_t color)
{
    const int sx = x;

    for (unsigned i = 0; i < text.length(); ++i)
    {
        unsigned char c = text[i];

        if (c == '\t' || c == '\f' || c == '\r' || c == ' ')
        {
            x += SYMBOL_WIDTH / 2;
            continue;
        }
        if (c == '\n')
        {
            x = sx;
            y += SYMBOL_HEIGHT;
            continue;
        }

        float u = (float)(c % SYMBOLS_IN_ROW) / SYMBOL_WIDTH;
        float v = (float)(c / SYMBOLS_IN_ROW) / SYMBOL_HEIGHT;

        sprite(x, y, SYMBOL_WIDTH, SYMBOL_HEIGHT, {u, v, u + SYMBOL_UV_WIDTH, v + SYMBOL_UV_HEIGHT}, color);

        x += SYMBOL_WIDTH / 2;
    }
}

void UIBatch::frect(int x, int y, int w, int h, fcolor_t color)
{
    sprite(x, y, w, h, {-1.0f, -1.0f, -1.0f, -1.0f}, color);
}

void UIBatch::line(int x1, int y1, int x2, int y2, fcolor_t color)
{
    const float lx1 = (x1 * 2.0f) / Window::getWidth() - 1.0f;
    const float ly1 = 1.0f - (y1 * 2.0f) / Window::getHeight();
    const float lx2 = (x2 * 2.0f) / Window::getWidth() - 1.0f;
    const float ly2 = 1.0f - (y2 * 2.0f) / Window::getHeight();

    lines.emplace_back(lx1, ly1, -1.0, -1.0, color);
    lines.emplace_back(lx2, ly2, -1.0f, 1.0f, color);
}

void UIBatch::rect(int x, int y, int w, int h, fcolor_t color)
{
    const float lx1 = (x * 2.0f) / Window::getWidth() - 1.0f;
    const float ly1 = 1.0f - (y * 2.0f) / Window::getHeight();
    const float lx2 = ((x + w) * 2.0f) / Window::getWidth() - 1.0f;
    const float ly2 = 1.0f - ((y + h) * 2.0f) / Window::getHeight();
    
    lines.emplace_back(lx1, ly1, -1.0, -1.0, color);
    lines.emplace_back(lx2, ly1, -1.0f, 1.0f, color);

    lines.emplace_back(lx1, ly1, -1.0, -1.0, color);
    lines.emplace_back(lx1, ly2, -1.0f, 1.0f, color);

    lines.emplace_back(lx2, ly1, -1.0, -1.0, color);
    lines.emplace_back(lx2, ly2, -1.0f, 1.0f, color);

    lines.emplace_back(lx1, ly2, -1.0, -1.0, color);
    lines.emplace_back(lx2, ly2, -1.0f, 1.0f, color);
}

void UIBatch::render(AssetsLoader& assets)
{
    assets.getShader("ui")->use();
    assets.getTexture("fonts/font")->bindUnit();

    VBO.write(sprites.data(), sprites.size() * sizeof(ui_vertex_t));

    VAO.bind();

    VAO.drawElements(spriteIndices.size(), spriteIndices.data());
    
    VBO.write(lines.data(), lines.size() * sizeof(ui_vertex_t));

    VAO.draw(lines.size(), 0x0001);

    VAO.unbind();


    lines.clear();
    sprites.clear();
    spriteIndices.clear();
}