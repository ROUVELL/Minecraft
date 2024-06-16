#include "ChunksRenderer.hpp"

#include "Chunks.hpp"
#include "../math.hpp"
#include "../Window/Camera.hpp"
#include "../Graphics/LineBatch.hpp"
#include "../Loaders/AssetsLoader.hpp"

#include "../Voxels/Atlas.hpp"


inline constexpr const color_t BLOCK_BOX_COLOR { 250, 160 };


ChunksRenderer::ChunksRenderer(Chunks* const chunks, LineBatch* const lineBatch, const Camera* const camera)
    : chunks(chunks),
    lineBatch(lineBatch),
    camera(camera)
{
}

void ChunksRenderer::drawWorldAxis()
{
    const glm::vec lookAt = camera->getPosition() + camera->getDirection() * 0.2f;

    lineBatch->line(lookAt, lookAt + glm::vec3(0.03, 0.0, 0.0), colors::RED);
    lineBatch->line(lookAt, lookAt + glm::vec3(0.0, 0.03, 0.0), colors::GREEN);
    lineBatch->line(lookAt, lookAt + glm::vec3(0.0, 0.0, 0.03), colors::BLUE);
}

void ChunksRenderer::drawChunkBox()
{
    const int cx = floordiv<float>(camera->getPosition().x, CHUNK_SIDE);
    const int cz = floordiv<float>(camera->getPosition().z, CHUNK_SIDE);

    const float x = cx * CHUNK_SIDE;
    const float z = cz * CHUNK_SIDE;

    lineBatch->box(glm::vec3(x, 0.0f, z) - 0.09f, glm::vec3(CHUNK_SIDE, CHUNK_HEIGHT, CHUNK_SIDE) + 0.01f);
}

void ChunksRenderer::drawVoxelBox(glm::vec3 position)
{
    lineBatch->box(position - 0.01f, glm::vec3(1.02f), BLOCK_BOX_COLOR);
}

void ChunksRenderer::drawVoxelNormal(glm::vec3 position, glm::vec3 normal)
{
    position += 0.5f;
    lineBatch->line(position, position + normal, colors::BLACK);
}

void ChunksRenderer::render(AssetsLoader& assets, const Atlas& atlas) const
{
    Shader* const shader = assets.getShader("main");
    shader->use();
    shader->uniformMat4("projview", camera->getProjViewMatrix());

    atlas.getTexture().bindUnit();

    chunks->render(*shader);
}