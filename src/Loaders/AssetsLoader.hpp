#pragma once

#include <unordered_map>

#include "../Graphics/Texture.hpp"
#include "../Graphics/Shader.hpp"


class AssetsLoader
{
    std::unordered_map<std::string, Texture> textures;
    std::unordered_map<std::string, Shader> shaders;
    
public:
    AssetsLoader();
    AssetsLoader(const AssetsLoader&) = delete;
    AssetsLoader(AssetsLoader&&) = delete;
    ~AssetsLoader();

    // TODO: I think it would be better with templates

    bool textureExists(const std::string& name);
    bool shaderExists(const std::string& name);

    Texture loadTexture(const std::string& name);
    Shader loadShader(const std::string& name);

    Texture* loadAndSaveTexture(const std::string& name);
    Shader* loadAndSaveShader(const std::string& name);

    Texture* getTexture(const std::string& name);
    Shader* getShader(const std::string& name);
};