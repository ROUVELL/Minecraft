
#include "Shader.hpp"

#include <fstream>
#include <iostream>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>


bool loadFile(const std::string& path, std::string* dst)
{
	std::ifstream in(path, std::ios::binary);
	if (in)
	{
		in.seekg(0, std::ios::end);
		dst->resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&(*dst)[0], dst->size());
		return true;
	}
	return false;
}

void checkShaderError(GLuint shader, char type)
{
	GLint success;
	GLchar infoLog[512];

	if (type == 'V' || type == 'F')
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cerr << "SHADER::" << type << ": Compilation failed\n";
			std::cerr << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 512, nullptr, infoLog);
			std::cerr << "SHADER::P: linking failed\n";
			std::cerr << infoLog << std::endl;
		}
	}
}


Shader::Shader()
	: ID{ 0 }
{
}

Shader::Shader(const std::string& vPath, const std::string& fPath)
	: Shader()
{
	std::string vertexCode;
	std::string fragmentCode;

	if (!loadFile(vPath, &vertexCode) || !loadFile(fPath, &fragmentCode))
		std::cerr << "Can`t open shader file!\n";

	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);

	checkShaderError(vertex, 'V');


	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);

	checkShaderError(fragment, 'F');


	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	checkShaderError(ID, 'P');

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::Shader(Shader&& other) noexcept
	: ID(other.ID)
{
}

unsigned int Shader::findUniformLoc(const std::string& name) const
{
	return glGetUniformLocation(ID, name.c_str());
}

void Shader::uniformMatrix(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(findUniformLoc(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::del()
{
	glDeleteProgram(ID);
}