#pragma once

#include <glm/vec3.hpp>

#include "../typedefs.hpp"

class Chunks;

class Raycasting final
{
    Raycasting() = default;
    ~Raycasting() = default;

public:
    static glm::vec3 end;
    static glm::vec3 norm;
    static glm::vec3 iend;
    static voxel_t id;

    static bool rayCast(glm::vec3 start, glm::vec3 dir, const Chunks* const chunks);
};
