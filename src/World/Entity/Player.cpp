#include "Player.hpp"

#include "../Chunks.hpp"
#include "../../Window/Window.hpp"
#include "../../Window/Events.hpp"
#include "../../Window/keys.hpp"

#include "../Raycasting.hpp"
#include "../../Physics/Hitbox.hpp"
#include "../../Physics/Physics.hpp"


Player::Player(Chunks* const chunks, glm::vec3 pos, float speed)
    : camera(pos, 70.0f, Window::getAspect()),
    chunks(chunks),
    speed(speed)
{
}

void Player::update(double dt)
{
    if (!Events::cursorLocked())
        return;

    for (uint key = KEY_1; key < KEY_9; ++key)
        if (Events::justPressed(key))
            selected = key - KEY_0;

    camera.rotate(Events::getDx() * H_MOUSE_SENSETIVITY, -Events::getDy() * V_MOUSE_SENSETIVITY);

    if (Raycasting::id)
    {
        const glm::ivec3 ipos = Raycasting::iend;
        const glm::ivec3 inorm = Raycasting::norm;

        if (Events::justClicked(MOUSE_BUTTON_LEFT))
        {
            glm::ivec3 voxelPos = ipos + inorm;
            chunks->setVoxel(voxelPos.x, voxelPos.y, voxelPos.z, selected);
        }
        if (Events::justClicked(MOUSE_BUTTON_RIGHT))
            chunks->setVoxel(ipos.x, ipos.y, ipos.z, 0);
    }

    [[maybe_unused]] glm::vec3 oldPosition = camera.getPosition();

    float distance = speed * dt;
    if (Events::pressed(KEY_LEFT_SHIFT)) distance *= 3.0f;

    if (Events::pressed(KEY_W))         camera.moveForward(distance);
    if (Events::pressed(KEY_S))         camera.moveBackward(distance);
    if (Events::pressed(KEY_D))         camera.moveRight(distance);
    if (Events::pressed(KEY_A))         camera.moveLeft(distance);
    if (Events::pressed(KEY_SPACE))     camera.moveUp(distance);
    if (Events::pressed(KEY_LEFT_CTRL)) camera.moveDown(distance);

    if constexpr (PLAYER_COLLISION)
    {
        glm::vec3 velocity = camera.getPosition() - oldPosition;

        static hitbox_t hitbox;
        hitbox.min = oldPosition - glm::vec3{0.2f, 1.6f, 0.2f};
        hitbox.max = oldPosition + glm::vec3{0.2f, 0.1f, 0.2f};

        if (collide_with_chunk(*chunks, &hitbox, velocity))
            camera.setPosition(hitbox.min + glm::vec3{0.2f, 1.6f, 0.2f});
    }
}