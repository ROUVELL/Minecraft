#pragma once

#include <string>
#include <vector>

#include "../GL/Buffers/Buffer.hpp"
#include "../GL/Buffers/Vao.hpp"

inline constexpr const u32 UI_BATCH_LINES_CAPICITY = 16U;
inline constexpr const u32 UI_BATCH_SPRITES_CAPICITY = 512U;

class AssetsLoader;

class UIBatch final
{
    struct ui_vertex_t
    {
        float x, y;
        float u, v;
        u32 color;
    };

    Vao VAO;
    Buffer VBO;

    mutable std::vector<ui_vertex_t> lines;
    mutable std::vector<ui_vertex_t> sprites;  // text and filled rects

    mutable std::vector<u32> spriteIndices;


public:
    UIBatch() noexcept;
    UIBatch(const UIBatch&) = delete;
    UIBatch(UIBatch&&) noexcept = delete;
    ~UIBatch();

    void sprite(int x, int y, int w, int h, uv_region_t uvregion, color_t color = color_t{}) const noexcept;
    void text(const std::string& text, int x, int y, color_t color = color_t{}) const noexcept;
    void frect(int x, int y, int w, int h, color_t color = color_t{}) const noexcept;
    
    void line(int x1, int y1, int x2, int y2, color_t color = color_t{}) const noexcept;
    void rect(int x, int y, int w, int h, color_t color = color_t{}) const noexcept;

    void render(AssetsLoader& assets) noexcept;
};