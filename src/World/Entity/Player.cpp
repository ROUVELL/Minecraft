#include "Player.hpp"

#include "../Chunks.hpp"
#include "../../Window/Window.hpp"
#include "../../Window/Keyboard.hpp"
#include "../../Window/Mouse.hpp"

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
    for (uint key = KEY_1; key < KEY_9; ++key)
    {
        if (Keyboard::isJustPressed(key))
            selected = key - KEY_0;
    }

    if (Mouse::isCursorLocked())
    {
        camera.rotate(Mouse::getDx() * H_MOUSE_SENSETIVITY, -Mouse::getDy() * V_MOUSE_SENSETIVITY);

        if (Raycasting::id)
        {
            const glm::ivec3 ipos = Raycasting::iend;
            const glm::ivec3 inorm = Raycasting::norm;

            if (Mouse::isJustClicked(MOUSE_BUTTON_LEFT))
            {
                glm::ivec3 voxelPos = ipos + inorm;
                chunks->setVoxel(voxelPos.x, voxelPos.y, voxelPos.z, selected);
            }
            if (Mouse::isJustClicked(MOUSE_BUTTON_RIGHT))
                chunks->setVoxel(ipos.x, ipos.y, ipos.z, 0);
        }
    }

    [[maybe_unused]] glm::vec3 oldPosition = camera.getPosition();

    float distance = speed * dt;
    if (Keyboard::isPressed(KEY_LEFT_SHIFT)) distance *= 3.0f;

    if (Keyboard::isPressed(KEY_W))         camera.moveForward(distance);
    if (Keyboard::isPressed(KEY_S))         camera.moveBackward(distance);
    if (Keyboard::isPressed(KEY_D))         camera.moveRight(distance);
    if (Keyboard::isPressed(KEY_A))         camera.moveLeft(distance);
    if (Keyboard::isPressed(KEY_SPACE))     camera.moveUp(distance);
    if (Keyboard::isPressed(KEY_LEFT_CTRL)) camera.moveDown(distance);

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