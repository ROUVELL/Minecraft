#pragma once

#include <functional>

#include "Chunks.hpp"
#include "../Graphics/Mesh.hpp"

constexpr int CHUNK_SIDE = 16;
constexpr int CHUNK_HEIGHT = 64;
constexpr int CHUNK_AREA = CHUNK_SIDE * CHUNK_SIDE;
constexpr int CHUNK_VOLUME = CHUNK_AREA * CHUNK_HEIGHT;

using Generator = std::function<void(voxel_t*, int, int)>;

inline bool isValidPosition(int vx, int vy, int vz) noexcept
{
	return vx > -1 && vx < CHUNK_SIDE &&
			vy > -1 && vy < CHUNK_HEIGHT &&
			vz > -1 && vz < CHUNK_SIDE;
}

struct ChunkNeighboars;

struct ChunkPosition
{
	int x, z;
};

class Chunk final
{
	const Chunks* chunks;
	voxel_t voxels[CHUNK_VOLUME];

	Mesh mesh;
	ChunkPosition position;
	glm::mat4 model;

	bool modified;

public:

	Chunk(int cx, int cz, const Chunks* chunks);
	Chunk(const Chunk&) = delete;

	voxel_t at(int x, int y, int z) const { return voxels[x + y * CHUNK_AREA + z * CHUNK_SIDE]; }
	voxel_t get(int x, int y, int z) const { return (isValidPosition(x, y, z) ? at(x, y, z) : 0); }
	void set(int x, int y, int z, voxel_t id) { voxels[x + y * CHUNK_AREA + z * CHUNK_SIDE] = id; setModified(); }
	bool empty(int x, int y, int z) const { return get(x, y, z) == 0; }

	ChunkPosition getPosition() const { return position; }
	const glm::mat4& getModelMatrix() const { return model; }
	ChunkNeighboars getNeighboars() const { return chunks->neighboars(position.x, position.z); }

	void setVoxel(int x, int y, int z, voxel_t id);

	bool isModified() const { return modified; }
	void setModified() { modified = true; }

	void generate(Generator generator);
	void buildMesh();
	void rebuildMesh() { buildMesh(); }

	void onDelete();

	void render();

};
