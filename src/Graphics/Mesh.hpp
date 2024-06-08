#pragma once

#include <vector>


struct mesh_data
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
	unsigned VAO = 0;
	unsigned VBO = 0;
	unsigned EBO = 0;
	unsigned count = 0;

public:
	Mesh(const std::vector<unsigned int>& attrs);
	Mesh(const Mesh&) = default;
	Mesh(Mesh&& other) = default;
	~Mesh() = default;

	void build(const mesh_data& data);
	
	void render(unsigned int mode = 0x0004) const;

	void del();
};

