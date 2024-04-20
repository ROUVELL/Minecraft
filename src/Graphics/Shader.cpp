
#include "Shader.hpp"

#include <fstream>
#include <iostream>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>


Shader::Shader()
	: ID{ 0 }
{
}

Shader::Shader(unsigned int id)
	: ID{ id }
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

bool loadFile(const std::string& file, std::string* dst)
{
	std::ifstream in(file, std::ios::binary);
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

Shader loadShader(const std::string& vertexFile, const std::string& fragmentFile)
{
	std::string vertexCode;
	std::string fragmentCode;

	if (!loadFile(vertexFile, &vertexCode) || !loadFile(fragmentFile, &fragmentCode))
	{
		std::cerr << "Can`t open shader file!\n";
		return Shader(0);
	}

	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success){
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::cerr << "SHADER::VERTEX: compilation failed\n";
		std::cerr << infoLog << std::endl;
		return Shader(0);
	}

	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success){
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		std::cerr << "SHADER::FRAGMENT: compilation failed\n";
		std::cerr << infoLog << std::endl;
		return Shader(0);
	}

	// Shader Program
	GLuint ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success){
		glGetProgramInfoLog(ID, 512, nullptr, infoLog);
		std::cerr << "SHADER::PROGRAM: linking failed\n";
		std::cerr << infoLog << std::endl;

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		return Shader(0);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return Shader(ID);
}
