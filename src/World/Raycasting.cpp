#include "Raycasting.hpp"

#include <limits>
#include <math.h>

#include "Chunks.hpp"


glm::vec3 Raycasting::end{ 0.0f};
glm::vec3 Raycasting::norm{ 0.0f};
glm::vec3 Raycasting::iend{ 0.0f};
voxel_id Raycasting::id = 0;


bool Raycasting::rayCast(glm::vec3 start, glm::vec3 dir, const Chunks* const chunks)
{
	norm.x = 0.0f;
    norm.y = 0.0f;
    norm.z = 0.0f;
    id = 0;

	const float px = start.x;
	const float py = start.y;
	const float pz = start.z;

	const float dx = dir.x;
	const float dy = dir.y;
	const float dz = dir.z;

	float t = 0.0f;
	int ix = floor(px);
	int iy = floor(py);
	int iz = floor(pz);

	const float stepx = (dx > 0.0f) ? 1.0f : -1.0f;
	const float stepy = (dy > 0.0f) ? 1.0f : -1.0f;
	const float stepz = (dz > 0.0f) ? 1.0f : -1.0f;

	const float infinity = std::numeric_limits<float>::infinity();

	const float txDelta = (dx == 0.0f) ? infinity : std::abs(1.0f / dx);
	const float tyDelta = (dy == 0.0f) ? infinity : std::abs(1.0f / dy);
	const float tzDelta = (dz == 0.0f) ? infinity : std::abs(1.0f / dz);

	const float xdist = (stepx > 0) ? (ix + 1 - px) : (px - ix);
	const float ydist = (stepy > 0) ? (iy + 1 - py) : (py - iy);
	const float zdist = (stepz > 0) ? (iz + 1 - pz) : (pz - iz);

	float txMax = (txDelta < infinity) ? txDelta * xdist : infinity;
	float tyMax = (tyDelta < infinity) ? tyDelta * ydist : infinity;
	float tzMax = (tzDelta < infinity) ? tzDelta * zdist : infinity;

	int steppedIndex = -1;

	while (t < MAX_RAYCAST_DIST)
    {
		id = chunks->getVoxel(ix, iy, iz);
		if (id)
		{
			end.x = px + t * dx;
			end.y = py + t * dy;
			end.z = pz + t * dz;

			iend.x = ix;
			iend.y = iy;
			iend.z = iz;

			if      (steppedIndex == 0) norm.x = -stepx;
			else if (steppedIndex == 1) norm.y = -stepy;
			else                        norm.z = -stepz;

            return true;
		}
		if (txMax < tyMax) {
			if (txMax < tzMax) {
				ix += stepx;
				t = txMax;
				txMax += txDelta;
				steppedIndex = 0;
			} else {
				iz += stepz;
				t = tzMax;
				tzMax += tzDelta;
				steppedIndex = 2;
			}
		} else {
			if (tyMax < tzMax) {
				iy += stepy;
				t = tyMax;
				tyMax += tyDelta;
				steppedIndex = 1;
			} else {
				iz += stepz;
				t = tzMax;
				tzMax += tzDelta;
				steppedIndex = 2;
			}
		}
	}

	end.x = px + t * dx;
    end.y = py + t * dy;
    end.z = pz + t * dz;

    iend.x = ix;
    iend.y = iy;
    iend.z = iz;

	id = 0;
    
    return false;
}