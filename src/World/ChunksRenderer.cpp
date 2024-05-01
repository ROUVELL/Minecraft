#include "ChunksRenderer.hpp"

#include "Chunk.hpp"
#include "../math.hpp"
#include "../Window/Camera.hpp"
#include "../Graphics/LineBatch.hpp"
#include "../Loaders/AssetsLoader.hpp"


const glm::vec4 BLOCK_BOX_COLOR = glm::vec4(1.0, 1.0, 1.0, 0.6);


ChunksRenderer::ChunksRenderer(Chunks* const chunks, LineBatch* const lineBatch, Camera* const camera)
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
    int cx = floordiv(camera->getPosition().x, CHUNK_SIDE);
    int cz = floordiv(camera->getPosition().z, CHUNK_SIDE);

    const float x = cx * CHUNK_SIDE + (CHUNK_SIDE * 0.5f);
    const float z = cz * CHUNK_SIDE + (CHUNK_SIDE * 0.5f);

    lineBatch->box(glm::vec3(x, CHUNK_HEIGHT * 0.5f, z), glm::vec3(CHUNK_SIDE, CHUNK_HEIGHT, CHUNK_SIDE) + 0.01f);
}

void ChunksRenderer::drawVoxelBox(const glm::vec3& center)
{
    lineBatch->box(center, glm::vec3(1.01f), BLOCK_BOX_COLOR);
}

void ChunksRenderer::drawVoxelNormal(const glm::vec3& center, const glm::vec3& normal)
{
    lineBatch->line(center, center + normal, BLACK);
}

void ChunksRenderer::render(AssetsLoader& assets)
{
    Shader* shader = assets.getShader("main");
    shader->use();
    shader->uniformMat4("projview", camera->getProjViewMatrix());

    assets.getTexture("grass")->bind();

    chunks->render(*shader);
}