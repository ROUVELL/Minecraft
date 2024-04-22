#pragma once

#include <string>

class Image;

class Texture final
{
	unsigned int ID;
	int width, height;

public:
	Texture();
	Texture(const std::string& path);
	Texture(const Image& image);
	Texture(const Texture&) = delete;
	Texture(Texture&&) noexcept;
	~Texture() = default;

	unsigned int getID() const { return ID; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }

	void bind();
	void unbind();
	void del();
};