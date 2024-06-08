#pragma once


using b8 = bool;

using i8 =  signed char;
using i16 = signed short;
using i32 = signed int;
using i64 = signed long int;

using u8 =  unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long int;

using f32 =  float;
using f64 =  double;
using f128 = long double;


using voxel_id = u8;
using Generator = void (voxel_id*, int, int);
