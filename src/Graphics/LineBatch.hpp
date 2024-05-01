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
    MeshData meshData;
    
public:
    LineBatch();
    ~LineBatch();

    void line(const glm::vec3& p1, const glm::vec3& p2, const glm::vec4& color = glm::vec4{ 1.0f });
    void line(float x1, float y1, float z1,
                float x2, float y2, float z2,
                float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
    void box(const glm::vec3& center, const glm::vec3& size, const glm::vec4& color = glm::vec4{ 1.0f });

    void render(AssetsLoader& assets, const glm::mat4& projview);
};