#include "Chunks.hpp"

#include <limits>

#include "Chunk.hpp"
#include "Generators.hpp"
#include "../Graphics/Shader.hpp"
#include "../math.hpp"

Chunks::Chunks()
	: chunks(WORLD_AREA, nullptr),
	chunksTemp(WORLD_AREA, nullptr),
	ox(0), oz(0)
{
}

Chunks::~Chunks()
{
	for (int index = 0; index < WORLD_AREA; ++index)
		if (Chunk* chunk = chunks[index])
		{
			chunk->onDelete();
			delete chunk;
			chunks[index] = nullptr;
		}
}

Chunk* Chunks::getNearestModified() const
{
	int minDist = std::numeric_limits<int>::max();
	Chunk* nearest = nullptr;

	for (int cx = 1; cx < WORLD_SIZE - 1; ++cx)
		for (int cz = 1; cz < WORLD_SIZE - 1; ++cz)
		{
			int index = cx + cz * WORLD_SIZE;

			if (chunks[index]->isModified())
			{
				int dist = std::abs(cx - HALF_WORLD_SIZE) + std::abs(cz - HALF_WORLD_SIZE);
				if (dist < minDist)
				{
					minDist = dist;
					nearest = chunks[index];
				}
			}
		}

	return nearest;
}

uint8_t Chunks::getVoxel(int wx, int wy, int wz) const
{
	if (wy < 0 || wy >= CHUNK_HEIGHT)
		return 0;

	int cx = floordiv(wx, CHUNK_SIDE);
	int cz = floordiv(wz, CHUNK_SIDE);

	const Chunk* const chunk = getChunk(cx, cz);

	if (chunk == nullptr)
		return 0;

	int lx = wx - cx * CHUNK_SIDE;
	int lz = wz - cz * CHUNK_SIDE;

	return chunk->at(lx, wy, lz);
}

void Chunks::setVoxel(int wx, int wy, int wz, voxel_t id)
{
	if (wy < 0 || wy >= CHUNK_HEIGHT)
		return;

	int cx = floordiv(wx, CHUNK_SIDE);
	int cz = floordiv(wz, CHUNK_SIDE);

	Chunk* chunk = getChunk(cx, cz);

	if (chunk == nullptr)
		return;

	int lx = wx - cx * CHUNK_SIDE;
	int lz = wz - cz * CHUNK_SIDE;

	chunk->setVoxel(lx, wy, lz, id);
}

voxel_t Chunks::rayCast(glm::vec3 start, glm::vec3 dir, glm::vec3* end, glm::vec3* norm, glm::vec3* iend) const
{
	norm->x = norm->y = norm->z = 0.0f;

	float px = start.x;
	float py = start.y;
	float pz = start.z;

	float dx = dir.x;
	float dy = dir.y;
	float dz = dir.z;

	float t = 0.0f;
	int ix = floor(px);
	int iy = floor(py);
	int iz = floor(pz);

	float stepx = (dx > 0.0f) ? 1.0f : -1.0f;
	float stepy = (dy > 0.0f) ? 1.0f : -1.0f;
	float stepz = (dz > 0.0f) ? 1.0f : -1.0f;

	float infinity = std::numeric_limits<float>::infinity();

	float txDelta = (dx == 0.0f) ? infinity : abs(1.0f / dx);
	float tyDelta = (dy == 0.0f) ? infinity : abs(1.0f / dy);
	float tzDelta = (dz == 0.0f) ? infinity : abs(1.0f / dz);

	float xdist = (stepx > 0) ? (ix + 1 - px) : (px - ix);
	float ydist = (stepy > 0) ? (iy + 1 - py) : (py - iy);
	float zdist = (stepz > 0) ? (iz + 1 - pz) : (pz - iz);

	float txMax = (txDelta < infinity) ? txDelta * xdist : infinity;
	float tyMax = (tyDelta < infinity) ? tyDelta * ydist : infinity;
	float tzMax = (tzDelta < infinity) ? tzDelta * zdist : infinity;

	int steppedIndex = -1;

	while (t <= MAX_RAYCAST_DIST){
		voxel_t id = getVoxel(ix, iy, iz);
		if (id)
		{
			end->x = px + t * dx;
			end->y = py + t * dy;
			end->z = pz + t * dz;

			iend->x = ix;
			iend->y = iy;
			iend->z = iz;

			if      (steppedIndex == 0) norm->x = -stepx;
			else if (steppedIndex == 1) norm->y = -stepy;
			else                        norm->z = -stepz;

			return id;
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
	iend->x = ix;
	iend->y = iy;
	iend->z = iz;

	end->x = px + t * dx;
	end->y = py + t * dy;
	end->z = pz + t * dz;

	return 0;
}

void Chunks::shift(int dx, int dz)
{
	if (dx == 0 && dz == 0)
		return;

	for (int index = 0; index < WORLD_AREA; ++index)
	{
		Chunk* chunk = chunks[index];

		if (!chunk)
			continue;

		int newCx = (index % WORLD_SIZE) - dx;
		int newCz = (index / WORLD_SIZE) - dz;

		if (newCx < 0 || WORLD_SIZE <= newCx || newCz < 0 || WORLD_SIZE <= newCz)
		{
			chunk->onDelete();
			delete chunk;
			chunks[index] = nullptr;
		}
		else
			chunksTemp[newCx + newCz * WORLD_SIZE] = chunk;
	}

	ox += dx;
	oz += dz;

	for (int index = 0; index < WORLD_AREA; ++index)
		if (chunksTemp[index] == nullptr)
		{
			chunksTemp[index] = new Chunk(index % WORLD_SIZE + ox, index / WORLD_SIZE + oz, this);
			chunksTemp[index]->generate(flatGenerator);
		}
	
	std::swap(chunks, chunksTemp);

	for (int i = 0; i < WORLD_AREA; ++i)
		chunksTemp[i] = nullptr;
}

void Chunks::centeredAt(int wx, int wz)
{
	int cx = floordiv(wx, CHUNK_SIDE);
	int cz = floordiv(wz, CHUNK_SIDE);

	int offsetX = cx - (WORLD_SIZE / 2);
	int offsetZ = cz - (WORLD_SIZE / 2);

	shift(offsetX - ox, offsetZ - oz);
}

void Chunks::update()
{
	if (Chunk* nearest = getNearestModified())
	{
		ChunkNeighboars n = nearest->getNeighboars();

		if (n.right && n.left && n.front && n.back)
		{
			nearest->buildMesh();

			if (nearest->needRebuildNeighboars())
			{
				nearest->setNeedRebuildNeighboars(false);

				if (n.right->isModified()) n.right->buildMesh();
				if (n.left ->isModified()) n.left->buildMesh();
				if (n.front->isModified()) n.front->buildMesh();
				if (n.back ->isModified()) n.back->buildMesh();
			}
		}
	}
}

void Chunks::render(Shader& shader)
{
	for (int cx = 1; cx < WORLD_SIZE - 1; ++cx)
		for (int cz = 1; cz < WORLD_SIZE - 1; ++cz)
			{
				Chunk* chunk = chunks[cx + cz * WORLD_SIZE];
				shader.uniformMatrix("model", chunk->getModelMatrix());
				chunk->render();
			}
}

