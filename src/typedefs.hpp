#pragma once

#include <cstdint>
#include <functional>


using voxel_t = uint8_t;
using Generator = void (voxel_t*, int, int);
