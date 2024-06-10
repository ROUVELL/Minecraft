#include "Chunk.hpp"

#include <cstring>

#include <glm/gtc/matrix_transform.hpp>

#include "ChunkMeshBuilder.hpp"


Chunk::Chunk(int cx, int cz, const Chunks* chunks)
	: chunks(chunks),
	position{cx, cz}
{
	memset(voxels, 0, CHUNK_VOLUME);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(position.x * CHUNK_SIDE, 0, position.z * CHUNK_SIDE));

	VAO.setAttrData(0, 3, 0);
	VAO.setAttrData(1, 2, 3 * sizeof(float));

	VBO.create(nullptr, MAX_VISIBLE_FACES * 4 * sizeof(chunk_vertex_t), buffer_usage::DYNAMIC_DRAW);

	VAO.bindVBO(VBO.getID(), sizeof(chunk_vertex_t));
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
	u32 verticesCount = 0;
	static chunk_vertex_t verts[MAX_VISIBLE_FACES * 4];

	buildChunkMesh(*this, verts, indices, verticesCount, indicesCount);

	VBO.write(verts, verticesCount * sizeof(chunk_vertex_t));

	modified = false;
}

void Chunk::onDelete()
{
	VAO.del();
	VBO.del();

	chunk_neighboars n = getNeighboars();

	if (n.left ) n.left->setModified();
	if (n.right) n.right->setModified();
	if (n.back ) n.back->setModified();
	if (n.front) n.front->setModified();
}

void Chunk::render() const
{
	VAO.bind();
	VAO.drawElements(indicesCount, indices);
	VAO.unbind();
}

