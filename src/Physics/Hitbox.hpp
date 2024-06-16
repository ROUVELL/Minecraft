#pragma once

#include <glm/common.hpp>
#include <glm/ext/vector_float3.hpp>


struct hitbox_t
{
    glm::vec3 min = glm::vec3{0.0f};
    glm::vec3 max = glm::vec3{1.0f};

    inline constexpr glm::vec3 get_size() const noexcept
    {
        return glm::abs(max - min);
    }

    inline constexpr glm::vec3 get_center() const noexcept
    {
        return (max + min) / 2.0f;
    }

    inline constexpr hitbox_t move(glm::vec3 vel) const noexcept
    {
        return hitbox_t{ .min = min + vel, .max = max + vel };
    }

    inline constexpr void move_ip(glm::vec3 vel) noexcept
    {
        min += vel;
        max += vel;
    }
};