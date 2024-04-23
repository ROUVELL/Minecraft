#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "World/ChunksRenderer.hpp"

class Engine final
{
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Chunks> chunks;
    std::shared_ptr<LineBatch> lineBatch;

    ChunksRenderer chunksRenderer;

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