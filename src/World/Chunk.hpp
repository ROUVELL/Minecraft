#pragma once

#include <functional>
#include <glm/mat4x4.hpp>

#include "Chunks.hpp"
#include "../Graphics/Mesh.hpp"


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

	bool rebuildNeighboars;
	bool modified;

public:
	Chunk(int cx, int cz, const Chunks* chunks);
	Chunk(const Chunk&) = delete;
	~Chunk() = default;

	bool isModified() const                   { return modified; }
	bool needRebuildNeighboars() const        { return rebuildNeighboars; }

	voxel_t at(int x, int y, int z) const     { return voxels[x + y * CHUNK_AREA + z * CHUNK_SIDE]; }
	voxel_t get(int x, int y, int z) const    { return (isValidPosition(x, y, z) ? at(x, y, z) : 0); }
	bool empty(int x, int y, int z) const     { return get(x, y, z) == 0; }
	void set(int x, int y, int z, voxel_t id) { voxels[x + y * CHUNK_AREA + z * CHUNK_SIDE] = id; setModified(); }

	ChunkPosition getPosition() const         { return position; }
	const glm::mat4& getModelMatrix() const   { return model; }
	ChunkNeighboars getNeighboars() const     { return chunks->neighboars(position.x, position.z); }

	void setModified()                        { modified = true; }
	void setNeedRebuildNeighboars(bool flag)  { rebuildNeighboars = flag; }

	void setVoxel(int x, int y, int z, voxel_t id);

	void generate(Generator generator);
	void buildMesh();

	void onDelete();

	void render() const;

};
