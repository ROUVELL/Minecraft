#include "ChunkMeshBuilder.hpp"

#include "../Graphics/Mesh.hpp"
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

	for (int y = 0; y < CHUNK_HEIGHT; ++y)
		for (int z = 0; z < CHUNK_SIDE; ++z)
			for (int x = 0; x < CHUNK_SIDE; ++x)
			{
				float id = (float)chunk.at(x, y, z);

				if (!id)
					continue;

				ChunkNeighboars n = chunk.getNeighboars();


				if ((z + 1 != CHUNK_SIDE) ? chunk.empty(x, y, z + 1) : (n.front->at(x, y, 0) == 0))  // front face
				{
					newVertex(x    , y + 1, z + 1, 0, 0, id);  // top left
					newVertex(x + 1, y + 1, z + 1, 1, 0, id);  // top right
					newVertex(x + 1, y    , z + 1, 1, 1, id);  // bottom right
					newVertex(x    , y    , z + 1, 0, 1, id);  // bottom left

					updateIndices();
				}

				if ((z > 0) ? chunk.empty(x, y, z - 1) : (n.back->at(x, y, CHUNK_SIDE - 1) == 0))  // back face
				{
					newVertex(x + 1, y + 1, z, 0, 0, id);  // top left
					newVertex(x    , y + 1, z, 1, 0, id);  // top right
					newVertex(x    , y    , z, 1, 1, id);  // bottom right
					newVertex(x + 1, y    , z, 0, 1, id);  // bottom left

					updateIndices();
				}

				if ((x + 1 != CHUNK_SIDE) ? chunk.empty(x + 1, y, z) : (n.right->at(0, y, z) == 0))  // right face
				{
					newVertex(x + 1, y + 1, z + 1, 0, 0, id);  // top left
					newVertex(x + 1, y + 1, z    , 1, 0, id);  // top right
					newVertex(x + 1, y    , z    , 1, 1, id);  // bottom right
					newVertex(x + 1, y    , z + 1, 0, 1, id);  // bottom left

					updateIndices();
				}

				if ((x > 0) ? chunk.empty(x - 1, y, z) : (n.left->at(CHUNK_SIDE - 1, y, z) == 0))  // left face
				{
					newVertex(x, y + 1, z    , 0, 0, id);  // top left
					newVertex(x, y + 1, z + 1, 1, 0, id);  // top right
					newVertex(x, y    , z + 1, 1, 1, id);  // bottom right
					newVertex(x, y    , z    , 0, 1, id);  // bottom left

					updateIndices();
				}
				
				if (chunk.empty(x, y + 1, z))  // top face
				{
					newVertex(x    , y + 1, z    , 0, 0, id);  // top left
					newVertex(x + 1, y + 1, z    , 1, 0, id);  // top right
					newVertex(x + 1, y + 1, z + 1, 1, 1, id);  // bottom right
					newVertex(x    , y + 1, z + 1, 0, 1, id);  // bottom left

					updateIndices();
				}

				if (chunk.empty(x, y - 1, z))  // bottom face
				{
					newVertex(x    , y, z + 1, 0, 0, id);  // top left
					newVertex(x + 1, y, z + 1, 1, 0, id);  // top right
					newVertex(x + 1, y, z    , 1, 1, id);  // bottom right
					newVertex(x    , y, z    , 0, 1, id);  // bottom left

					updateIndices();
				}
			}
}

















