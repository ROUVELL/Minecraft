#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "Mesh.hpp"

const glm::vec4 RED = glm::vec4(1.0, 0.0, 0.0, 1.0);
const glm::vec4 GREEN = glm::vec4(0.0, 1.0, 0.0, 1.0);
const glm::vec4 BLUE = glm::vec4(0.0, 0.0, 1.0, 1.0);
const glm::vec4 BLACK = glm::vec4(0.0, 0.0, 0.0, 1.0);

class AssetsLoader;

class LineBatch final
{
    Mesh mesh;
    mesh_data meshData;
    
public:
    LineBatch();
    ~LineBatch();

    void line(glm::vec3 p1, glm::vec3 p2,
            glm::vec4 color = glm::vec4{ 1.0f }) { line(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, color.r, color.g, color.b, color.a); }
    void line(float x1, float y1, float z1,
                float x2, float y2, float z2,
                glm::vec4 color = glm::vec4{ 1.0f }) { line(x1, y1, z1, x2, y2, z2, color.r, color.g, color.b, color.a); }
    void line(float x1, float y1, float z1,
                float x2, float y2, float z2,
                float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
    void box(glm::vec3 center, glm::vec3 size, glm::vec4 color = glm::vec4{ 1.0f });

    void render(AssetsLoader& assets, const glm::mat4& projview);
};