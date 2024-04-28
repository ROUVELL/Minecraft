#pragma once

#include <glm/gtc/noise.hpp>

#include "../constants.hpp"
#include "../typedefs.hpp"


inline void flatGenerator(voxel_t* voxels, int, int) noexcept
{
	for (int lz = 0; lz < CHUNK_SIDE; ++lz)
		for (int lx = 0; lx < CHUNK_SIDE; ++lx)
			voxels[lx + lz * CHUNK_SIDE] = 1;
};

inline void simplexGenerator(voxel_t* voxels, int cx, int cz) noexcept
{
	for (int lz = 0; lz < CHUNK_SIDE; ++lz)
		for (int lx = 0; lx < CHUNK_SIDE; ++lx)
		{
			int wx = lx + cx * CHUNK_SIDE;
			int wz = lz + cz * CHUNK_SIDE;

			int height = (int)(glm::simplex(glm::vec2(wx, wz) * 0.01f) * 16.0f + 32.0f);

			for (int ly = 0; ly < std::min(height, CHUNK_HEIGHT); ++ly)
				voxels[lx + ly * CHUNK_AREA + lz * CHUNK_SIDE] = 1 + ((cx << 2) ^ (cz << 6));
	 	}
};