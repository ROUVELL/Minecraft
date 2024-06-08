#include "Mesh.hpp"

#include <numeric>
#include <GL/glew.h>


Mesh::Mesh(const std::vector<unsigned int>& attrs)
	: VAO(0), VBO(0), IBO(0), count(0)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	const unsigned int vertexSize = std::reduce(attrs.begin(), attrs.end()) * sizeof(GLfloat);
	unsigned int offset = 0;
	for (unsigned int i = 0; i < attrs.size(); ++i)
	{
		glVertexAttribPointer(i, attrs[i], GL_FLOAT, GL_FALSE, vertexSize, (GLvoid*)(unsigned long)offset);
		glEnableVertexAttribArray(i);
		offset += attrs[i] * sizeof(GLfloat);
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::Mesh(Mesh&& other) noexcept
	: VAO(other.VAO), VBO(other.VBO), IBO(other.IBO), count(other.count)
{
	other.VAO = other.VBO = other.IBO = other.count = 0;
}

void Mesh::build(const MeshData& data)
{
	count = data.indices.size();

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.vertices.size() * sizeof(GLfloat), data.vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indices.size() * sizeof(GLuint), data.indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::render() const
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::render(unsigned int mode) const
{
	glBindVertexArray(VAO);
	glDrawElements(mode, count, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::del()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteVertexArrays(1, &VAO);
	VAO = VBO = IBO = count = 0;
}
