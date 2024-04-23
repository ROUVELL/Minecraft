#pragma once

#include <vector>
#include <cstdint>

#include <glm/fwd.hpp>

#include "../constants.hpp"

using voxel_t = uint8_t;

inline bool isValidPosition(int cx, int cz) noexcept
{
	return cx > -1 && cx < WORLD_SIZE &&
			cz > -1 && cz < WORLD_SIZE;
}

class Chunk;
class Shader;

struct ChunkNeighboars
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
	int ox, oz;

	ChunkNeighboars neighboarsLocal(int cx, int cz) const { return { getChunkLocal(cx + 1, cz), getChunkLocal(cx - 1, cz), getChunkLocal(cx, cz + 1), getChunkLocal(cx, cz - 1)};}
	Chunk* getChunkLocal(int cx, int cz) const { return isValidPosition(cx, cz) ? chunks[cx + cz * WORLD_SIZE] : nullptr; }

public:
	Chunks();
	Chunks(const Chunks&) = delete;
	Chunks(Chunks&&) noexcept = delete;
	~Chunks();

	ChunkNeighboars neighboars(int cx, int cz) const { return { getChunk(cx + 1, cz), getChunk(cx - 1, cz), getChunk(cx, cz + 1), getChunk(cx, cz - 1) }; }
	Chunk* getChunk(int cx, int cz) const { return getChunkLocal(cx - ox, cz - oz); }
	voxel_t getVoxel(int x, int y, int z) const;

	void setVoxel(int x, int y, int z, voxel_t id);

	voxel_t rayCast(glm::vec3 start, glm::vec3 dir, glm::vec3* end, glm::vec3* norm, glm::vec3* iend) const;

	void shift(int dx, int dz);
	void centeredAt(int wx, int wz);

	void update();
	void render(Shader& shader);
};

