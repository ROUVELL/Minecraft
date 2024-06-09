#include "Mesh.hpp"

#include <numeric>
#include <GL/glew.h>


Mesh::Mesh(const std::vector<unsigned int>& attrs)
{
	// TODO: Delete EBO buffer
	// TODO: Rebuild method
	// TODO: Allocate buffer memory here

	unsigned int offset = 0;
	for (unsigned int i = 0; i < attrs.size(); ++i)
	{
		VAO.setAttrData(i, attrs[i], offset);

		offset += attrs[i] * sizeof(GLfloat);
	}

	VAO.bindVBO(VBO.getID(), std::reduce(attrs.begin(), attrs.end()) * sizeof(GLfloat));
	VAO.bindEBO(EBO.getID());
}

void Mesh::build(const mesh_data& data)
{
	count = data.indices.size();

	VBO.create(data.vertices.data(), data.vertices.size() * sizeof(GLfloat), buffer_usage::DYNAMIC_DRAW);
	EBO.create(data.indices.data(), data.indices.size() * sizeof(GLuint), buffer_usage::DYNAMIC_DRAW);
}

void Mesh::render(unsigned int mode) const
{
	VAO.bind();
	VAO.drawElements(count, nullptr, mode);
	VAO.unbind();
}

void Mesh::del()
{
	VAO.del();
	VBO.del();
	EBO.del();
	count = 0;
}
