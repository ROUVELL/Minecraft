#include "Mesh.hpp"

#include <numeric>
#include <GL/glew.h>


Mesh::Mesh(const std::vector<unsigned int>& attrs)
{
	// TODO: Delete EBO buffer
	// TODO: Rebuild method
	// TODO: Allocate buffer memory here

	glCreateVertexArrays(1, &VAO);
	glCreateBuffers(1, &VBO);
	glCreateBuffers(1, &EBO);

	unsigned int offset = 0;
	for (unsigned int i = 0; i < attrs.size(); ++i)
	{
		glVertexArrayAttribFormat(VAO, i, attrs[i], GL_FLOAT, GL_FALSE, offset);
		glVertexArrayAttribBinding(VAO, i, 0);
		glEnableVertexArrayAttrib(VAO, i);

		offset += attrs[i] * sizeof(GLfloat);
	}

	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, std::reduce(attrs.begin(), attrs.end()) * sizeof(GLfloat));
	glVertexArrayElementBuffer(VAO, EBO);
}

void Mesh::build(const mesh_data& data)
{
	count = data.indices.size();

	glNamedBufferData(VBO, data.vertices.size() * sizeof(GLfloat), data.vertices.data(), GL_DYNAMIC_DRAW);
	glNamedBufferData(EBO, data.indices.size() * sizeof(GLuint), data.indices.data(), GL_DYNAMIC_DRAW);
}

void Mesh::render(unsigned int mode) const
{
	glBindVertexArray(VAO);
	glDrawElements(mode, count, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}

void Mesh::del()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
	VAO = VBO = EBO = count = 0;
}
