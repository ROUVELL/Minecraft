#pragma once

#include <unordered_map>

#include "../GL/Texture.hpp"
#include "../GL/Shader.hpp"


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

    bool textureExists(const std::string& name) const;
    bool shaderExists(const std::string& name) const;

    Texture loadTexture(const std::string& name) const;
    Shader loadShader(const std::string& name) const;

    Texture* loadAndSaveTexture(const std::string& name);
    Shader* loadAndSaveShader(const std::string& name);

    Texture* getTexture(const std::string& name);
    Shader* getShader(const std::string& name);
};