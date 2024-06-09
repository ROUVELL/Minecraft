#pragma once

#include <string>

#include "../GL/Buffers/Buffer.hpp"
#include "../GL/Buffers/Vao.hpp"

inline constexpr const u32 TEXT_BATCH_CAPICITY = 512U;  // characters

class AssetsLoader;

class TextBatch final
{
    struct char_vertex_t
    {
        float x, y;
        float u, v;
        float r, g, b, a;
    };

    Vao VAO;
    Buffer VBO;

    char_vertex_t vertices[TEXT_BATCH_CAPICITY];
    u32 indices[TEXT_BATCH_CAPICITY * 6];

    u32 count = 0;  // for indices
    u32 index = 0;  // for vertices


public:
    TextBatch();
    TextBatch(const TextBatch&) = delete;
    TextBatch(TextBatch&&) noexcept = delete;
    ~TextBatch();

    void text(const std::string& text, int x, int y, float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);

    void render(AssetsLoader& assets);
};