#include "Player.hpp"

#include "../Chunks.hpp"
#include "../../Window/Keyboard.hpp"
#include "../../Window/Mouse.hpp"

#include "../Raycasting.hpp"


Player::Player(Chunks* const chunks, glm::vec3 pos)
    : camera(pos, 70.0f), chunks(chunks), selected(1), speed(30.0)
{
}

void Player::processEvents()
{

}

void Player::update(double dt)
{
    for (uint key = KEY_1; key <= KEY_9; ++key)
    {
        if (Keyboard::isJustPressed(key))
            selected = key - KEY_0;
    }

    if (Mouse::isCursorLocked())
    {
        camera.yaw(-Mouse::getDx() * 0.2f * dt);
        camera.pitch(-Mouse::getDy() * 0.1f * dt);

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

    float distance = speed * dt;
    if (Keyboard::isPressed(KEY_LEFT_SHIFT)) distance *= 3.0;

    if (Keyboard::isPressed(KEY_W)) camera.moveForward(distance);
    if (Keyboard::isPressed(KEY_S)) camera.moveBackward(distance);
    if (Keyboard::isPressed(KEY_D)) camera.moveRight(distance);
    if (Keyboard::isPressed(KEY_A)) camera.moveLeft(distance);
    if (Keyboard::isPressed(KEY_SPACE))      camera.moveUp(distance);
    if (Keyboard::isPressed(KEY_LEFT_CTRL)) camera.moveDown(distance);
}