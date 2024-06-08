#pragma once

#include <glm/ext/vector_float3.hpp>

class Chunks;
class LineBatch;
class Camera;
class AssetsLoader;
class Atlas;

class ChunksRenderer final
{
    Chunks* const       chunks;
    LineBatch* const    lineBatch;
    const Camera* const camera;

public:
    ChunksRenderer(Chunks* const chunks, LineBatch* const lineBatch, const Camera* const camera);
    ChunksRenderer(const ChunksRenderer&) = delete;
    ChunksRenderer(ChunksRenderer&&) noexcept = delete;
    ~ChunksRenderer() = default;

    void drawWorldAxis();
    void drawChunkBox();
    void drawVoxelBox(glm::vec3 center);
    void drawVoxelNormal(glm::vec3 center, glm::vec3 normal);
    
    void render(AssetsLoader& assets, const Atlas& atlas) const;
};