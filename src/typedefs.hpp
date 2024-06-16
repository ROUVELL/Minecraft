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

struct fcolor_t
{
    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;
    float a = 1.0f;
};
