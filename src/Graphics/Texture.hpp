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
	Texture(const Texture&) = delete;  // TODO: Probably need to implement a full copy of the texture (with a new ID of course)
	Texture(Texture&&) noexcept;
	~Texture() = default;

	void fromFile(const std::string& path);
	void fromImage(const Image& image);

	unsigned int getID() const { return ID; }
	int getWidth()       const { return width; }
	int getHeight()      const { return height; }

	void bind() const;
	void unbind() const;
	void del();
};