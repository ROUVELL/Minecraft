#include "AssetsLoader.hpp"

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

const std::string TEXTURES_FOLDER = "../res/textures/";
const std::string SHADERS_FOLDER = "../res/shaders/";


AssetsLoader::AssetsLoader()
{
}

AssetsLoader::~AssetsLoader()
{
    for (auto& texture : textures)
        texture.second.del();

    for (auto& shader : shaders)
        shader.second.del();
}

bool AssetsLoader::textureExists(const std::string& name)
{
    return fs::exists(TEXTURES_FOLDER + name + ".png");
}

bool AssetsLoader::shaderExists(const std::string& name)
{
    return fs::exists(SHADERS_FOLDER + name + ".glslv") && fs::exists(SHADERS_FOLDER + name + ".glslf");
}

Texture AssetsLoader::loadTexture(const std::string& name)
{
    if (textureExists(name))
        return Texture(TEXTURES_FOLDER + name + ".png");

    std::cout << "Texture not exits: '" << name << "'! An empty texture was returned!\n";

    return Texture();
}

Shader AssetsLoader::loadShader(const std::string& name)
{
    if (shaderExists(name))
    {
        return Shader(SHADERS_FOLDER + name);
    }
    
    std::cout << "Shader not exits: '" << name << "'! An empty shader was returned!\n";

    return Shader();
}

Texture* AssetsLoader::loadAndSaveTexture(const std::string& name)
{
    if (textureExists(name))
    {
        textures.emplace(name, Texture(TEXTURES_FOLDER + name + ".png"));
        return &textures[name];
    }

    std::cout << "Texture not exits: '" << name << "'!\n";

    return nullptr;
}
Shader* AssetsLoader::loadAndSaveShader(const std::string& name)
{
    if (shaderExists(name))
    {
        shaders.emplace(name, Shader(SHADERS_FOLDER + name));
        return &shaders[name];
    }
    
    std::cout << "Shader not exits: '" << name << "'!\n";

    return nullptr;
}

Texture* AssetsLoader::getTexture(const std::string& name)
{
    if (textures.contains(name))
        return &textures[name];

    return loadAndSaveTexture(name);
}

Shader* AssetsLoader::getShader(const std::string& name)
{
    if (shaders.contains(name))
        return &shaders[name];

    return loadAndSaveShader(name);
}
