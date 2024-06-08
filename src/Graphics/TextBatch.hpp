#pragma once

#include <string>

#include "../Graphics/Mesh.hpp"

class AssetsLoader;

class TextBatch final
{
    Mesh mesh;
    mesh_data meshData;

    unsigned int index;

public:
    TextBatch();
    TextBatch(const TextBatch&) = delete;
    TextBatch(TextBatch&&) noexcept = delete;
    ~TextBatch();

    void text(const std::string& text, int x, int y, float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);

    void render(AssetsLoader& assets);
};