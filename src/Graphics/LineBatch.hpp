#pragma once

#include <glm/ext/vector_float3.hpp>
#include <glm/ext/matrix_float4x4.hpp>

#include "../GL/Buffers/Buffer.hpp"
#include "../GL/Buffers/Vao.hpp"


inline constexpr const u32 LINE_BATCH_CAPACITY = 32U;


class AssetsLoader;

struct point_t
{
    glm::vec3 pos;
    u32 color;
};


class LineBatch final
{
    Vao VAO;
    Buffer VBO;

    point_t linesData[LINE_BATCH_CAPACITY * 2];
    u32 count = 0;
    
public:
    LineBatch();
    LineBatch(const LineBatch&) = delete;
    LineBatch(LineBatch&&) = delete;
    ~LineBatch();

    void line(glm::vec3 p1, glm::vec3 p2, color_t color = color_t{});

    void line(float x1, float y1, float z1,
                float x2, float y2, float z2,
                color_t color = color_t{}) { line({x1, y1, z1}, {x2, y2, z2}, color); }


    void box(glm::vec3 position, glm::vec3 size, color_t color = color_t{});

    void render(AssetsLoader& assets, const glm::mat4& projview);
};