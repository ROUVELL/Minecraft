#include "Generators.hpp"

#include <chrono>

#include <glm/gtc/noise.hpp>


i64 random_int() noexcept
{
	auto now = std::chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
}

void simplexGenerator(voxel_id* voxels, int cx, int cz) noexcept
{
	for (int lz = 0; lz < CHUNK_SIDE; ++lz)
		for (int lx = 0; lx < CHUNK_SIDE; ++lx)
		{
			int wx = lx + cx * CHUNK_SIDE;
			int wz = lz + cz * CHUNK_SIDE;

			int height = (int)(glm::simplex(glm::vec2(wx, wz) * 0.01f) * 16.0f + 32.0f);

			for (int ly = 0; ly < std::min(height, CHUNK_HEIGHT); ++ly)
				voxels[lx + ly * CHUNK_AREA + lz * CHUNK_SIDE] = ly / (CHUNK_HEIGHT / 8);
	 	}
};