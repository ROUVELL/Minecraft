#pragma once

#include <string>

class Texture final
{
	unsigned int ID;
	int width, height;

public:
	Texture();
	Texture(unsigned int id, int w, int h);
	~Texture() = default;

	unsigned int getID() const { return ID; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }

	void bind();
	void unbind();
	void del();
};


Texture loadTexture(const std::string& file);