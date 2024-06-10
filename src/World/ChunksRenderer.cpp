#include "ChunksRenderer.hpp"

#include "Chunk.hpp"
#include "../math.hpp"
#include "../Window/Camera.hpp"
#include "../Graphics/LineBatch.hpp"
#include "../Loaders/AssetsLoader.hpp"

#include "../Voxels/Atlas.hpp"


inline constexpr const glm::vec4 BLOCK_BOX_COLOR = glm::vec4(1.0f, 1.0f, 1.0f, 0.6f);


ChunksRenderer::ChunksRenderer(Chunks* const chunks, LineBatch* const lineBatch, const Camera* const camera)
    : chunks(chunks),
    lineBatch(lineBatch),
    camera(camera)
{
}

void ChunksRenderer::drawWorldAxis()
{
    const glm::vec lookAt = camera->getPosition() + camera->getDirection() * 0.2f;

    lineBatch->line(lookAt, lookAt + glm::vec3(0.03, 0.0, 0.0), RED);
    lineBatch->line(lookAt, lookAt + glm::vec3(0.0, 0.03, 0.0), GREEN);
    lineBatch->line(lookAt, lookAt + glm::vec3(0.0, 0.0, 0.03), BLUE);
}

void ChunksRenderer::drawChunkBox()
{
    const int cx = floordiv(camera->getPosition().x, CHUNK_SIDE);
    const int cz = floordiv(camera->getPosition().z, CHUNK_SIDE);

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
    lineBatch->line(position, position + normal, BLACK);
}

void ChunksRenderer::render(AssetsLoader& assets, const Atlas& atlas) const
{
    Shader* const shader = assets.getShader("main");
    shader->use();
    shader->uniformMat4("projview", camera->getProjViewMatrix());

    atlas.getTexture().bindUnit();

    chunks->render(*shader);
}