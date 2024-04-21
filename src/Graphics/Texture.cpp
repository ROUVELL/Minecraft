#include "Texture.hpp"

#include <iostream>
#include <GL/glew.h>

#include "../vendors/stb/stb_image.hpp"

Texture::Texture()
	: ID{ 0 }, width{ 0 }, height{ 0 }
{
}

Texture::Texture(unsigned int id, int w, int h)
	: ID{ id }, width{ w }, height{ h }
{
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::del()
{
	glDeleteTextures(1, &ID);
}

Texture loadTexture(const std::string& file)
{
	int width, height, channels;
	unsigned char* bytes = stbi_load(file.c_str(), &width, &height, &channels, 0);

	int alpha;
	if (channels == 3)
		alpha = GL_RGB;
	else if (channels == 4)
		alpha = GL_RGBA;
	else
	{
		std::cerr << "Unknown image color type!\n";
		stbi_image_free(bytes);
		return Texture(0, 0, 0);
	}

	GLuint ID;
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, alpha, GL_UNSIGNED_BYTE, bytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(bytes);

	return Texture(ID, width, height);
}
