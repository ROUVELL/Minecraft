#pragma once

#include <glm/mat4x4.hpp>

#include "Chunks.hpp"

#include "../GL/Buffers/Buffer.hpp"
#include "../GL/Buffers/Vao.hpp"


inline bool isValidPosition(int vx, int vy, int vz) noexcept
{
	return vx > -1 && vx < CHUNK_SIDE &&
			vy > -1 && vy < CHUNK_HEIGHT &&
			vz > -1 && vz < CHUNK_SIDE;
}

struct chunk_neighboars;

struct chunk_pos
{
	int x, z;
};

struct chunk_vertex_t
{
	float x, y, z;
	float u, v;
};

class Chunk final
{
	inline constexpr static const u32 MAX_VISIBLE_BLOCKS = H_CHUNK_SIDE * H_CHUNK_SIDE * H_CHUNK_HEIGHT;
	inline constexpr static const u32 MAX_VISIBLE_FACES = MAX_VISIBLE_BLOCKS * 6;

	const Chunks* chunks;
	voxel_id voxels[CHUNK_VOLUME];
	
	Vao VAO;
	Buffer VBO;
	u32 indices[MAX_VISIBLE_FACES * 6];
	u32 indicesCount = 0;

	chunk_pos position;
	glm::mat4 model;

	bool rebuildNeighboars = false;
	bool modified = false;
	bool wasModified = false;  // at least once

public:
	Chunk(int cx, int cz, const Chunks* chunks);
	Chunk(const Chunk&) = delete;
	~Chunk() = default;

	bool isModified() const                   { return modified; }
	bool isWasModified() const                { return wasModified; }
	bool needRebuildNeighboars() const        { return rebuildNeighboars; }

	voxel_id at(int x, int y, int z) const    { return voxels[x + y * CHUNK_AREA + z * CHUNK_SIDE]; }
	voxel_id get(int x, int y, int z) const   { return (isValidPosition(x, y, z) ? at(x, y, z) : 0); }
	bool empty(int x, int y, int z) const     { return get(x, y, z) == 0; }

	chunk_pos getPosition() const             { return position; }
	const glm::mat4& getModelMatrix() const   { return model; }
	chunk_neighboars getNeighboars() const    { return chunks->neighboars(position.x, position.z); }
	const voxel_id* getConstData() const      { return voxels; }
	voxel_id* getData()                       { return voxels; }

	void setModified()                        { modified = true; }
	void setNeedRebuildNeighboars(bool flag)  { rebuildNeighboars = flag; }

	void setVoxel(int x, int y, int z, voxel_id id);

	void generate(Generator generator);
	void buildMesh();

	void onDelete();

	void render() const;

};
