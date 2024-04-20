#pragma once

#include <string>
#include <glm/fwd.hpp>

class Shader final
{
	unsigned int ID;

	unsigned int findUniformLoc(const std::string& name) const;

public:
	Shader();
	Shader(unsigned int id);
	~Shader() = default;

	void uniformMatrix(const std::string& name, const glm::mat4& matrix);

	void use();
	void del();
};

Shader loadShader(const std::string& vertexFileName, const std::string& fragmentFileName);
