#pragma once

#include <vector>

struct MeshData
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	void addVertex(float x, float y, float z, float u, float v, float voxelId)
	{
		vertices.insert(vertices.end(), {x, y, z, u, v, voxelId});
	}

	void updateIndices(unsigned int index)
	{
		indices.insert(indices.end(), {index, index + 1, index + 2, index, index + 2, index + 3});
	}
};

class Mesh final
{
	unsigned int VAO, VBO, IBO, count;

public:
	Mesh(const std::vector<unsigned int>& attrs);

	void build(const MeshData& data);
	void render();
	void render(unsigned int mode);

	void del();
};

