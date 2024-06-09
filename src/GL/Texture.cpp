#include "Texture.hpp"

#include <math.h>

#include <GL/glew.h>

#include "../vendors/stb/stb_image.hpp"
#include "../Graphics/Image.hpp"


inline constexpr GLenum externalFormat(uint32_t channels) noexcept
{
	return (channels == 4) ? GL_RGBA : GL_RGB;
}

inline constexpr GLenum internalFormat(unsigned channels) noexcept
{
	return (channels == 4) ? GL_RGBA8 : GL_RGB8;
}


Texture::Texture()
{
	glCreateTextures(GL_TEXTURE_2D, 1, &ID);
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

void Texture::fromFile(const std::string& path)
{
	int width, height, channels;
	unsigned char* bytes = stbi_load(path.c_str(), &width, &height, &channels, 0);

	fromBytes(width, height, channels, bytes);

	stbi_image_free(bytes);
}

void Texture::fromImage(const Image& image)
{
	fromBytes(image.getWidth(), image.getHeight(), image.getChannels(), image.getData());
}

void Texture::fromBytes(int width, int height, int channels, const unsigned char* const bytes)
{
	glTextureStorage2D(ID, 1 + std::floor(std::log2(std::max(width, height))), internalFormat(channels), width, height);
	glTextureSubImage2D(ID, 0, 0, 0, width, height, externalFormat(channels), GL_UNSIGNED_BYTE, bytes);

	glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(ID, GL_TEXTURE_MAX_LEVEL, 5);

	glGenerateTextureMipmap(ID);
}

void Texture::bindUnit(unsigned location) const
{
	glBindTextureUnit(location, ID);
}

void Texture::del()
{
	glDeleteTextures(1, &ID);
	ID = 0;
}