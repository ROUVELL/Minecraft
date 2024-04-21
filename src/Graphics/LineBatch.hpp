#include <glm/glm.hpp>

#include "Mesh.hpp"
#include "Shader.hpp"

class LineBatch final
{
    Mesh mesh;
    MeshData meshData;
    Shader shader;
    
public:
    LineBatch();
    ~LineBatch();

    void line(const glm::vec3& p1, const glm::vec3& p2, const glm::vec4& color = glm::vec4{ 1.0f });
    void line(float x1, float y1, float z1,
                float x2, float y2, float z2,
                float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
    void box(const glm::vec3& center, const glm::vec3& size, const glm::vec4& color = glm::vec4{ 1.0f });

    void render(const glm::mat4& projview);
};