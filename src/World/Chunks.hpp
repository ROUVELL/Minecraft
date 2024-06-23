#pragma once

#include <vector>

#include "WorldFiles.hpp"
#include "../constants.hpp"
#include "../typedefs.hpp"

inline bool isValidPosition(int cx, int cz) noexcept
{
	return cx > -1 && cx < WORLD_SIZE &&
			cz > -1 && cz < WORLD_SIZE;
}

class Chunk;
class Shader;

struct chunk_neighboars
{
	Chunk* right;
	Chunk* left;
	Chunk* front;
	Chunk* back;
};

class Chunks final
{
	std::vector<Chunk*> chunks;
	std::vector<Chunk*> chunksTemp;
	int ox = 0;
	int oz = 0;

	WorldFiles worldFiles;

	chunk_neighboars neighboarsLocal(int cx, int cz) const { return { getChunkLocal(cx + 1, cz), getChunkLocal(cx - 1, cz), getChunkLocal(cx, cz + 1), getChunkLocal(cx, cz - 1)};}
	Chunk* getChunkLocal(int cx, int cz) const             { return isValidPosition(cx, cz) ? chunks[cx + cz * WORLD_SIZE] : nullptr; }
	Chunk* getNearestModified() const;

public:
	Chunks();
	Chunks(const Chunks&) = delete;
	Chunks(Chunks&&) noexcept = delete;
	~Chunks();

	chunk_neighboars neighboars(int cx, int cz) const { return { getChunk(cx + 1, cz), getChunk(cx - 1, cz), getChunk(cx, cz + 1), getChunk(cx, cz - 1) }; }
	Chunk* getChunk(int cx, int cz) const             { return getChunkLocal(cx - ox, cz - oz); }
	voxel_id getVoxel(int x, int y, int z) const;

	void setVoxel(int x, int y, int z, voxel_id id);

	void shift(int dx, int dz);
	void centeredAt(int wx, int wz);
	void clear();

	void update();
	void render(Shader& shader) const;
};

