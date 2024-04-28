#include <memory>

#include "../Window/Camera.hpp"
#include "../Graphics/LineBatch.hpp"
#include "Chunk.hpp"

class AssetsLoader;

class ChunksRenderer
{
    std::shared_ptr<Chunks> chunks;
    std::shared_ptr<LineBatch> lineBatch;
    std::shared_ptr<Camera> camera;

public:
    ChunksRenderer(const std::shared_ptr<Chunks>& chunks,
                    const std::shared_ptr<LineBatch>& lineBatch,
                    const std::shared_ptr<Camera>& camera);
    ChunksRenderer(const ChunksRenderer&) = delete;
    ChunksRenderer(ChunksRenderer&&) noexcept = delete;
    ~ChunksRenderer() = default;

    void drawWorldAxis();
    void drawChunkBox();
    void drawVoxelBox(const glm::vec3& center);
    void drawVoxelNormal(const glm::vec3& center, const glm::vec3& normal);
    
    void render(AssetsLoader& assets);
};