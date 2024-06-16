#pragma once


#include <glm/ext/vector_float3.hpp>

class Chunks;
struct hitbox_t;

/*
    Resolves the collision of a hitbox with a chunks. Returns true if the collision occurs

    Accepts a hitbox and its velocity vector.
    Depending on the velocity direction, it checks the corresponding voxels.
    The function automatically calculates a new position if there are collisions
*/
bool collide_with_chunk(
    const Chunks& chunks,
    hitbox_t* const hitbox,
    glm::vec3 velocity
);