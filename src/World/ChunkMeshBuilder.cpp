#include "ChunkMeshBuilder.hpp"

#include "../Voxels/Blocks.hpp"
#include "Chunk.hpp"


void buildChunkMesh(const Chunk& chunk,
                    chunk_vertex_t* vertices,
                    unsigned int* indices,
                    unsigned int& verticesCount,
                    unsigned int& indicesCount)
{
	indicesCount = 0;
	verticesCount = 0;

	auto newVertex = [&vertices, &verticesCount](float x, float y, float z, float u, float v) -> void
	{
		vertices[verticesCount++] = { x, y, z, u, v };
	};

	auto updateIndices = [&indices, &indicesCount, &verticesCount]() -> void
	{
		indices[indicesCount++] = verticesCount;
		indices[indicesCount++] = verticesCount + 1;
		indices[indicesCount++] = verticesCount + 2;
		indices[indicesCount++] = verticesCount;
		indices[indicesCount++] = verticesCount + 2;
		indices[indicesCount++] = verticesCount + 3;
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
					updateIndices();

					newVertex(x    , y + 1, z + 1, regs.front.u1, regs.front.v1);  // top left
					newVertex(x + 1, y + 1, z + 1, regs.front.u2, regs.front.v1);  // top right
					newVertex(x + 1, y    , z + 1, regs.front.u2, regs.front.v2);  // bottom right
					newVertex(x    , y    , z + 1, regs.front.u1, regs.front.v2);  // bottom left
				}

				if ((z > 0) ? chunk.empty(x, y, z - 1) : (n.back->at(x, y, CHUNK_SIDE - 1) == 0))  // back face
				{
					updateIndices();

					newVertex(x + 1, y + 1, z, regs.back.u1, regs.back.v1);  // top left
					newVertex(x    , y + 1, z, regs.back.u2, regs.back.v1);  // top right
					newVertex(x    , y    , z, regs.back.u2, regs.back.v2);  // bottom right
					newVertex(x + 1, y    , z, regs.back.u1, regs.back.v2);  // bottom left
				}

				if ((x + 1 != CHUNK_SIDE) ? chunk.empty(x + 1, y, z) : (n.right->at(0, y, z) == 0))  // right face
				{
					updateIndices();

					newVertex(x + 1, y + 1, z + 1, regs.right.u1, regs.right.v1);  // top left
					newVertex(x + 1, y + 1, z    , regs.right.u2, regs.right.v1);  // top right
					newVertex(x + 1, y    , z    , regs.right.u2, regs.right.v2);  // bottom right
					newVertex(x + 1, y    , z + 1, regs.right.u1, regs.right.v2);  // bottom left
				}

				if ((x > 0) ? chunk.empty(x - 1, y, z) : (n.left->at(CHUNK_SIDE - 1, y, z) == 0))  // left face
				{
					updateIndices();

					newVertex(x, y + 1, z    , regs.left.u1, regs.left.v1);  // top left
					newVertex(x, y + 1, z + 1, regs.left.u2, regs.left.v1);  // top right
					newVertex(x, y    , z + 1, regs.left.u2, regs.left.v2);  // bottom right
					newVertex(x, y    , z    , regs.left.u1, regs.left.v2);  // bottom left
				}
				
				if (chunk.empty(x, y + 1, z))  // top face
				{
					updateIndices();

					newVertex(x    , y + 1, z    , regs.top.u1, regs.top.v1);  // top left
					newVertex(x + 1, y + 1, z    , regs.top.u2, regs.top.v1);  // top right
					newVertex(x + 1, y + 1, z + 1, regs.top.u2, regs.top.v2);  // bottom right
					newVertex(x    , y + 1, z + 1, regs.top.u1, regs.top.v2);  // bottom left
				}

				if (chunk.empty(x, y - 1, z))  // bottom face
				{
					updateIndices();

					newVertex(x    , y, z + 1, regs.bottom.u1, regs.bottom.v1);  // top left
					newVertex(x + 1, y, z + 1, regs.bottom.u2, regs.bottom.v1);  // top right
					newVertex(x + 1, y, z    , regs.bottom.u2, regs.bottom.v2);  // bottom right
					newVertex(x    , y, z    , regs.bottom.u1, regs.bottom.v2);  // bottom left
				}
			}
}

















