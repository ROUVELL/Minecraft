#include "Chunks.hpp"

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

	int cx = modfloordiv(wx, CHUNK_SIDE);
	int cz = modfloordiv(wz, CHUNK_SIDE);

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

	int cx = modfloordiv(wx, CHUNK_SIDE);
	int cz = modfloordiv(wz, CHUNK_SIDE);

	Chunk* chunk = getChunk(cx, cz);

	if (chunk == nullptr)
		return;

	int lx = wx - cx * CHUNK_SIDE;
	int lz = wz - cz * CHUNK_SIDE;

	chunk->setVoxel(lx, wy, lz, id);
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
	int cx = modfloordiv(wx, CHUNK_SIDE);
	int cz = modfloordiv(wz, CHUNK_SIDE);

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

void Chunks::render(Shader& shader) const
{
	for (int cx = 1; cx < WORLD_SIZE - 1; ++cx)
		for (int cz = 1; cz < WORLD_SIZE - 1; ++cz)
		{
			const Chunk* const chunk = chunks[cx + cz * WORLD_SIZE];
			shader.uniformMat4("model", chunk->getModelMatrix());
			chunk->render();
		}
}

