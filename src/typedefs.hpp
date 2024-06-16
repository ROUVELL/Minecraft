#pragma once


using b8 = bool;

using i8 =  char;
using i16 = short;
using i32 = int;
using i64 = long int;

using u8 =  unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long int;

using f32 =  float;
using f64 =  double;


using voxel_id = u8;
using Generator = void (voxel_id*, int, int);


struct uv_region_t
{
    float u1 = 0.0f;
    float v1 = 0.0f;
    float u2 = 1.0f;
    float v2 = 1.0f;
};

union color_t
{
    struct
    {
        u8 r, g, b, a;
    };

    u32 value;  // AABBGGRR

    constexpr color_t(u8 scalar = 255, u8 alpha = 255) noexcept : r(scalar), g(scalar), b(scalar), a(alpha) { }
    constexpr color_t(u8 r, u8 g, u8 b, u8 a = 255) noexcept : r(r), g(g), b(b), a(a) { }
};

namespace colors
{
    inline constexpr const color_t WHITE{255};
    inline constexpr const color_t BLACK{ 0};
    inline constexpr const color_t RED{ 255, 0, 0 };
    inline constexpr const color_t GREEN{ 0, 255, 0 };
    inline constexpr const color_t BLUE{ 0, 0, 255 };
    inline constexpr const color_t TRANSPARENT{ 0, 0 };
}
