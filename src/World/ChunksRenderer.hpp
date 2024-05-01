#pragma once

#include <glm/fwd.hpp>

class Chunks;
class LineBatch;
class Camera;
class AssetsLoader;

class ChunksRenderer
{
    Chunks* const chunks;
    LineBatch* const lineBatch;
    Camera* const camera;

public:
    ChunksRenderer(Chunks* const chunks, LineBatch* const lineBatch, Camera* const camera);
    ChunksRenderer(const ChunksRenderer&) = delete;
    ChunksRenderer(ChunksRenderer&&) noexcept = delete;
    ~ChunksRenderer() = default;

    void drawWorldAxis();
    void drawChunkBox();
    void drawVoxelBox(const glm::vec3& center);
    void drawVoxelNormal(const glm::vec3& center, const glm::vec3& normal);
    
    void render(AssetsLoader& assets);
};