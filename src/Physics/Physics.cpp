#include "Physics.hpp"

#include "Hitbox.hpp"
#include "../World/Chunks.hpp"


bool collide_with_chunk(
    const Chunks& chunks,
    hitbox_t* const hitbox,
    glm::vec3 velocity
)
{
    bool collision = false;

    const float w = hitbox->get_size().x;
    const float h = hitbox->get_size().y;
    const float d = hitbox->get_size().z;


    if (velocity.y)
    {
        hitbox->move_ip({ 0.0f, velocity.y, 0.0f });

        const int max_y = std::floor(hitbox->max.y);
        const int min_y = std::floor(hitbox->min.y);

        for (int wx = std::floor(hitbox->min.x); wx <= std::floor(hitbox->max.x); ++wx)
            for (int wz = std::floor(hitbox->min.z); wz <= std::floor(hitbox->max.z); ++wz)
            {
                if (velocity.y > 0.0f)
                {
                    if (chunks.getVoxel(wx, max_y, wz) != 0)
                    {
                        hitbox->max.y = max_y - 0.000001f;
                        hitbox->min.y = max_y - 0.000001f - h;

                        collision = true;
                    }
                }
                else if (velocity.y < 0.0f)
                {
                    if (chunks.getVoxel(wx, min_y, wz) != 0)
                    {
                        hitbox->min.y = min_y + 1.000001f;
                        hitbox->max.y = min_y + 1.000001f + h;

                        collision = true;
                    }
                }
            }
    }

    if (velocity.x)
    {
        hitbox->move_ip({ velocity.x, 0.0f, 0.0f });

        const int max_x = std::floor(hitbox->max.x);
        const int min_x = std::floor(hitbox->min.x);

        for (int wz = std::floor(hitbox->min.z); wz <= std::floor(hitbox->max.z); ++wz)
            for (int wy = std::floor(hitbox->min.y); wy <= std::floor(hitbox->max.y); ++wy)
            {
                if (velocity.x > 0.0f)
                {
                    if (chunks.getVoxel(max_x, wy, wz) != 0)
                    {
                        hitbox->max.x = max_x - 0.000001f;
                        hitbox->min.x = max_x - 0.000001f - w;

                        collision = true;
                    }
                }
                else if (velocity.x < 0.0f)
                {
                    if (chunks.getVoxel(min_x, wy, wz) != 0)
                    {
                        hitbox->min.x = min_x + 1.000001f;
                        hitbox->max.x = min_x + 1.000001f + w;

                        collision = true;
                    }
                }

            }
    }
    
    if (velocity.z)
    {
        hitbox->move_ip({ 0.0f, 0.0f, velocity.z });

        const int max_z = std::floor(hitbox->max.z);
        const int min_z = std::floor(hitbox->min.z);

        for (int wx = std::floor(hitbox->min.x); wx <= std::floor(hitbox->max.x); ++wx)
            for (int wy = std::floor(hitbox->min.y); wy <= std::floor(hitbox->max.y); ++wy)
            {
                if (velocity.z > 0.0f)
                {
                    if (chunks.getVoxel(wx, wy, max_z) != 0)
                    {
                        hitbox->max.z = max_z - 0.000001f;
                        hitbox->min.z = max_z - 0.000001f - d;

                        collision = true;
                    }
                }
                else if (velocity.z < 0.0f)
                {
                    if (chunks.getVoxel(wx, wy, min_z) != 0)
                    {
                        hitbox->min.z = min_z + 1.000001f;
                        hitbox->max.z = min_z + 1.000001f + d;

                        collision = true;
                    }
                }
            }
    }

    return collision;
}