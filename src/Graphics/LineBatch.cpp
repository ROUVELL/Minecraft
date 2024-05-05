#include "LineBatch.hpp"

#include "../Loaders/AssetsLoader.hpp"

LineBatch::LineBatch()
    : mesh({ 3, 4 })
{
}

LineBatch::~LineBatch()
{
    mesh.del();
}

void LineBatch::line(float x1, float y1, float z1,
            float x2, float y2, float z2,
            float r, float g, float b, float a)
{
    const unsigned int count = meshData.indices.size();

    meshData.vertices.insert(meshData.vertices.end(), { x1, y1, z1, r, g, b, a, x2, y2, z2, r, g, b, a });
    meshData.indices.insert(meshData.indices.end(), {count, count + 1});
}

void LineBatch::box(glm::vec3 center, glm::vec3 size, glm::vec4 color)
{
    float w = size.x;
    float h = size.y;
    float d = size.z;

    float sx = center.x - (w * 0.5f);
    float sy = center.y - (h * 0.5f);
    float sz = center.z - (d * 0.5f);

    line(sx, sy    , sz    , sx + w, sy    , sz    , color);
    line(sx, sy + h, sz    , sx + w, sy + h, sz    , color);
    line(sx, sy    , sz + d, sx + w, sy    , sz + d, color);
    line(sx, sy + h, sz + d, sx + w, sy + h, sz + d, color);

    line(sx    , sy, sz    , sx    , sy + h, sz    , color);
    line(sx + w, sy, sz    , sx + w, sy + h, sz    , color);
    line(sx    , sy, sz + d, sx    , sy + h, sz + d, color);
    line(sx + w, sy, sz + d, sx + w, sy + h, sz + d, color);

    line(sx    , sy    , sz, sx    , sy    , sz + d, color);
    line(sx + w, sy    , sz, sx + w, sy    , sz + d, color);
    line(sx    , sy + h, sz, sx    , sy + h, sz + d, color);
    line(sx + w, sy + h, sz, sx + w, sy + h, sz + d, color);
}

void LineBatch::render(AssetsLoader& assets, const glm::mat4& projview)
{
    Shader* shader = assets.getShader("line");
    shader->use();
    shader->uniformMat4("projview", projview);

    mesh.build(meshData);
    mesh.render(0x0001);  // GL_LINES

    meshData.vertices.clear();
    meshData.indices.clear();
}