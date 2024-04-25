#pragma once

#include <string>
#include <glm/fwd.hpp>

class Shader final
{
	unsigned int ID;

	unsigned int findUniformLoc(const std::string& name) const;

public:
	Shader();
	Shader(const std::string& path);
	Shader(const std::string& vPath, const std::string& fPath);
	Shader(const Shader&) = delete;  // It's probably not necessary.
	Shader(Shader&& other) noexcept;
	~Shader() = default;

	void uniformFloat(const std::string& name, float value);
	void uniformMatrix(const std::string& name, const glm::mat4& matrix);

	void use();
	void del();
};