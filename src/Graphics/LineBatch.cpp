#include "LineBatch.hpp"

#include "../Loaders/AssetsLoader.hpp"


LineBatch::LineBatch()
{
    VAO.setAttrData(0, 3, 0);
    VAO.setAttrData(1, 1, 3 * sizeof(float), attr_type::UNSIGNED_INT);

    VBO.create(nullptr, LINE_BATCH_CAPACITY * 2 * sizeof(point_t));

    VAO.bindVBO(VBO.getID(), sizeof(point_t));
}

LineBatch::~LineBatch()
{
    VAO.del();
    VBO.del();
}

void LineBatch::line(glm::vec3 p1, glm::vec3 p2, color_t color)
{
    linesData[count++] = point_t{ p1, color.value };
    linesData[count++] = point_t{ p2, color.value };
}

void LineBatch::box(glm::vec3 position, glm::vec3 size, color_t color)
{
    float w = size.x;
    float h = size.y;
    float d = size.z;

    float sx = position.x;
    float sy = position.y;
    float sz = position.z;

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

    VBO.write(linesData, count * sizeof(point_t));

    VAO.bind();
    VAO.draw(count, 0x0001);  // GL_LINES
    VAO.unbind();

    count = 0;
}