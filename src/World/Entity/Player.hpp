#pragma once

#include "../../Window/Camera.hpp"
#include "../../typedefs.hpp"

class Chunks;

class Player
{
    Camera camera;
    Chunks* const chunks;

    voxel_id selected = 1;

    float speed;

public:
    Player(Chunks* const chunks, glm::vec3 pos, float speed = 20.0f);
    Player(const Player&) = delete;
    Player(Player&&) noexcept = delete;
    ~Player() = default;

    const Camera* getCamera() const { return &camera; }
    voxel_id getSelected() const    { return selected; }

    void update(double dt);
};