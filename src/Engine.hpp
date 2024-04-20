#pragma once

#include <string>
#include <unordered_map>

#include "Window/Camera.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/LineBatch.hpp"
#include "World/Chunks.hpp"

class Engine final
{
    Camera camera;
    Chunks chunks;
    LineBatch lineBatch;

    std::unordered_map<std::string, Texture> textures;
    std::unordered_map<std::string, Shader> shaders;

    double dt;
    uint64_t frame;

    void updateDt();
    void processEvents();
    void update();
    void render();

public:
    Engine();
    ~Engine();

    double getDt() const { return dt; }
    uint64_t getFrame() const { return frame; }

    void run();
    void stop();
};