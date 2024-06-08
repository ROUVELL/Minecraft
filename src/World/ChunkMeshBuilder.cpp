#include "ChunkMeshBuilder.hpp"

#include "../Graphics/Mesh.hpp"
#include "../Voxels/Blocks.hpp"
#include "Chunk.hpp"


void buildChunkMesh(const Chunk& chunk, MeshData* meshData)
{
	unsigned int index = 0;

	auto newVertex = [meshData](float x, float y, float z, float u, float v, float voxelId) -> void
	{
		meshData->addVertex(x, y, z, u, v, voxelId);
	};

	auto updateIndices = [meshData, &index]() -> void
	{
		meshData->updateIndices(index);
		index += 4;
	};

	chunk_neighboars n = chunk.getNeighboars();

	if (!(n.front && n.back && n.left && n.right))
		return;

	for (int y = 0; y < CHUNK_HEIGHT; ++y)
		for (int z = 0; z < CHUNK_SIDE; ++z)
			for (int x = 0; x < CHUNK_SIDE; ++x)
			{
				voxel_id id = chunk.at(x, y, z);

				if (!id)
					continue;

				const UVRegions& regs = Blocks::getBlock(id).uv_regions;

				if ((z + 1 != CHUNK_SIDE) ? chunk.empty(x, y, z + 1) : (n.front->at(x, y, 0) == 0))  // front face
				{
					newVertex(x    , y + 1, z + 1, regs.front.u1, regs.front.v1, id);  // top left
					newVertex(x + 1, y + 1, z + 1, regs.front.u2, regs.front.v1, id);  // top right
					newVertex(x + 1, y    , z + 1, regs.front.u2, regs.front.v2, id);  // bottom right
					newVertex(x    , y    , z + 1, regs.front.u1, regs.front.v2, id);  // bottom left

					updateIndices();
				}

				if ((z > 0) ? chunk.empty(x, y, z - 1) : (n.back->at(x, y, CHUNK_SIDE - 1) == 0))  // back face
				{
					newVertex(x + 1, y + 1, z, regs.back.u1, regs.back.v1, id);  // top left
					newVertex(x    , y + 1, z, regs.back.u2, regs.back.v1, id);  // top right
					newVertex(x    , y    , z, regs.back.u2, regs.back.v2, id);  // bottom right
					newVertex(x + 1, y    , z, regs.back.u1, regs.back.v2, id);  // bottom left

					updateIndices();
				}

				if ((x + 1 != CHUNK_SIDE) ? chunk.empty(x + 1, y, z) : (n.right->at(0, y, z) == 0))  // right face
				{
					newVertex(x + 1, y + 1, z + 1, regs.right.u1, regs.right.v1, id);  // top left
					newVertex(x + 1, y + 1, z    , regs.right.u2, regs.right.v1, id);  // top right
					newVertex(x + 1, y    , z    , regs.right.u2, regs.right.v2, id);  // bottom right
					newVertex(x + 1, y    , z + 1, regs.right.u1, regs.right.v2, id);  // bottom left

					updateIndices();
				}

				if ((x > 0) ? chunk.empty(x - 1, y, z) : (n.left->at(CHUNK_SIDE - 1, y, z) == 0))  // left face
				{
					newVertex(x, y + 1, z    , regs.left.u1, regs.left.v1, id);  // top left
					newVertex(x, y + 1, z + 1, regs.left.u2, regs.left.v1, id);  // top right
					newVertex(x, y    , z + 1, regs.left.u2, regs.left.v2, id);  // bottom right
					newVertex(x, y    , z    , regs.left.u1, regs.left.v2, id);  // bottom left

					updateIndices();
				}
				
				if (chunk.empty(x, y + 1, z))  // top face
				{
					newVertex(x    , y + 1, z    , regs.top.u1, regs.top.v1, id);  // top left
					newVertex(x + 1, y + 1, z    , regs.top.u2, regs.top.v1, id);  // top right
					newVertex(x + 1, y + 1, z + 1, regs.top.u2, regs.top.v2, id);  // bottom right
					newVertex(x    , y + 1, z + 1, regs.top.u1, regs.top.v2, id);  // bottom left

					updateIndices();
				}

				if (chunk.empty(x, y - 1, z))  // bottom face
				{
					newVertex(x    , y, z + 1, regs.bottom.u1, regs.bottom.v1, id);  // top left
					newVertex(x + 1, y, z + 1, regs.bottom.u2, regs.bottom.v1, id);  // top right
					newVertex(x + 1, y, z    , regs.bottom.u2, regs.bottom.v2, id);  // bottom right
					newVertex(x    , y, z    , regs.bottom.u1, regs.bottom.v2, id);  // bottom left

					updateIndices();
				}
			}
}

















