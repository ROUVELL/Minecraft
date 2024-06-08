#include "Chunk.hpp"

#include <cstring>

#include <glm/gtc/matrix_transform.hpp>

#include "ChunkMeshBuilder.hpp"


Chunk::Chunk(int cx, int cz, const Chunks* chunks)
	: chunks(chunks),
	mesh({ 3, 2, 1 }),
	position{cx, cz}
{
	memset(voxels, 0, CHUNK_VOLUME);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(position.x * CHUNK_SIDE, 0, position.z * CHUNK_SIDE));
}

void Chunk::setVoxel(int x, int y, int z, voxel_id id)
{
	if (!isValidPosition(x, y, z))
		return;

	voxels[x + y * CHUNK_AREA + z * CHUNK_SIDE] = id;
	
	setModified();
	wasModified = true;

	chunk_neighboars n = getNeighboars();

	if (x == 0 && n.left)
	{
		n.left->setModified();
		setNeedRebuildNeighboars(true);
	}
	else if ((x + 1) == CHUNK_SIDE && n.right)
	{
		n.right->setModified();
		setNeedRebuildNeighboars(true);
	}

	if (z == 0 && n.back)
	{
		n.back->setModified();
		setNeedRebuildNeighboars(true);
	}
	else if ((z + 1) == CHUNK_SIDE && n.front)
	{
		n.front->setModified();
		setNeedRebuildNeighboars(true);
	}
}

void Chunk::generate(Generator generator)
{
	generator(voxels, position.x, position.z);
	setModified();
}

void Chunk::buildMesh()
{
	MeshData meshData;

	buildChunkMesh(*this, &meshData);

	mesh.build(meshData);
	
	modified = false;
}

void Chunk::onDelete()
{
	mesh.del();

	chunk_neighboars n = getNeighboars();

	if (n.left ) n.left->setModified();
	if (n.right) n.right->setModified();
	if (n.back ) n.back->setModified();
	if (n.front) n.front->setModified();
}

void Chunk::render() const
{
	mesh.render();
}

