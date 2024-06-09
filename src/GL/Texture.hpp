#pragma once

#include <string>


class Image;

class Texture final
{
	unsigned int ID = 0;

public:
	Texture();
	Texture(const std::string& path);
	Texture(const Image& image);
	Texture(const Texture&) = default;
	Texture(Texture&&) noexcept = default;
	~Texture() = default;

	unsigned int getID() const { return ID; }

	void fromFile(const std::string& path);
	void fromImage(const Image& image);
	void fromBytes(int width, int height, int channels, const unsigned char* const bytes);

	void bindUnit(unsigned location = 0) const;
	void del();
};