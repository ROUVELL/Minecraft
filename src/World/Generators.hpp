#pragma once

#include "../constants.hpp"
#include "../typedefs.hpp"
#include "../math.hpp"


extern i64 random_int() noexcept;

template<int HEIGHT = 1, voxel_id ID = 1>
requires (HEIGHT > 0 && HEIGHT < CHUNK_HEIGHT && ID < 9)
inline void flatGenerator(voxel_id* voxels, int, int) noexcept
{
	for (int i = 0; i < (CHUNK_AREA * HEIGHT); ++i)
		voxels[i] = ID;
}

template<int HEIGHT = 1>
requires (HEIGHT > 0 && HEIGHT < CHUNK_HEIGHT)
void randomFlatGenerator(voxel_id* voxels, int cx, int cz) noexcept
{
    i64 r = random_int();
    voxel_id id = (abs(cx * (r >> 4 ) + cz * r) % 8) + 1;

	for (int i = 0; i < (CHUNK_AREA * HEIGHT); ++i)
		voxels[i] = id;
};

void simplexGenerator(voxel_id* voxels, int cx, int cz) noexcept;