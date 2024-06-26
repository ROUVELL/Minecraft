#include "Texture.hpp"

#include <GL/glew.h>

#include "../vendors/stb/stb_image.hpp"
#include "Image.hpp"

inline constexpr GLenum int2enum(uint32_t channels) noexcept
{
	return (channels == 4) ? GL_RGBA : (channels == 3) ? GL_RGB : GL_RED;
}

Texture::Texture()
	: ID{ 0 }, width{ 0 }, height{ 0 }
{
}

Texture::Texture(const std::string& path)
	: Texture()
{
	fromFile(path);
}

Texture::Texture(const Image& image)
	: Texture()
{
	fromImage(image);
}

Texture::Texture(Texture&& other) noexcept
	: ID(other.ID), width(other.width), height(other.height)
{
}

void Texture::fromFile(const std::string& path)
{
	if (ID != 0)
		del();

	int channels;
	unsigned char* bytes = stbi_load(path.c_str(), &width, &height, &channels, 0);

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, int2enum(channels), GL_UNSIGNED_BYTE, bytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 5);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(bytes);
}

void Texture::fromImage(const Image& image)
{
	if (ID != 0)
		del();

	width = image.getWidth();
	height = image.getHeight();

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, int2enum(image.getChannels()), GL_UNSIGNED_BYTE, image.getData());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 5);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::del()
{
	glDeleteTextures(1, &ID);
	ID = width = height = 0;
}