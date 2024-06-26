#pragma once

#include "../../Window/Camera.hpp"
#include "../../typedefs.hpp"

class Chunks;

class Player
{
    Camera camera;
    Chunks* const chunks;

    voxel_t selected;

    float speed;

public:
    Player(Chunks* const chunks, glm::vec3 pos);
    Player(const Player&) = delete;
    Player(Player&&) noexcept = delete;
    ~Player() = default;

    const Camera* getCamera() const { return &camera; }
    voxel_t getSelected() const     { return selected; }

    void processEvents();
    void update(double dt);
};