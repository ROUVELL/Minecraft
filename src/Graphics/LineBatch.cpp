#include "LineBatch.hpp"

#include "Shader.hpp"

LineBatch::LineBatch()
    : mesh({ 3, 4 }),
    shader("../res/shaders/line.glslv", "../res/shaders/line.glslf")
{
}

LineBatch::~LineBatch()
{
    mesh.del();
    shader.del();
}

void LineBatch::line(const glm::vec3& p1, const glm::vec3& p2, const glm::vec4& color)
{
    const unsigned int count = meshData.indices.size();

    meshData.vertices.insert(meshData.vertices.end(), { p1.x, p1.y, p1.z, color.x, color.y, color.z, color.w });
    meshData.vertices.insert(meshData.vertices.end(), { p2.x, p2.y, p2.z, color.x, color.y, color.z, color.w });
    meshData.indices.insert(meshData.indices.end(), {count, count + 1});
}

void LineBatch::line(float x1, float y1, float z1,
            float x2, float y2, float z2,
            float r, float g, float b, float a)
{
    const unsigned int count = meshData.indices.size();

    meshData.vertices.insert(meshData.vertices.end(), { x1, y1, z1, r, g, b, a, x2, y2, z2, r, g, b, a });
    meshData.indices.insert(meshData.indices.end(), {count, count + 1});
}

void LineBatch::box(const glm::vec3& center, const glm::vec3& size, const glm::vec4& color)
{
    float w = size.x;
    float h = size.y;
    float d = size.z;

    float sx = center.x - (w * 0.5f);
    float sy = center.y - (h * 0.5f);
    float sz = center.z - (d * 0.5f);

    float r = color.x;
    float g = color.y;
    float b = color.z;
    float a = color.w;

    line(sx, sy, sz, sx + w, sy, sz, r, g, b, a);
    line(sx, sy + h, sz, sx + w, sy + h, sz, r, g, b, a);
    line(sx, sy, sz + d, sx + w, sy, sz + d, r, g, b, a);
    line(sx, sy + h, sz + d, sx + w, sy + h, sz + d, r, g, b, a);

    line(sx, sy, sz, sx, sy + h, sz, r, g, b, a);
    line(sx + w, sy, sz, sx + w, sy + h, sz, r, g, b, a);
    line(sx, sy, sz + d, sx, sy + h, sz + d, r, g, b, a);
    line(sx + w, sy, sz + d, sx + w, sy + h, sz + d, r, g, b, a);

    line(sx, sy, sz, sx, sy, sz + d, r, g, b, a);
    line(sx + w, sy, sz, sx + w, sy, sz + d, r, g, b, a);
    line(sx, sy + h, sz, sx, sy + h, sz + d, r, g, b, a);
    line(sx + w, sy + h, sz, sx + w, sy + h, sz + d, r, g, b, a);
}

void LineBatch::render(const glm::mat4& projview)
{
    shader.use();
    shader.uniformMatrix("projview", projview);
    mesh.build(meshData);
    mesh.render(0x0001);  // GL_LINES

    meshData.vertices.clear();
    meshData.indices.clear();
}