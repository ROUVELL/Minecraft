#pragma once

#include <memory>

#include "World/ChunksRenderer.hpp"
#include "Loaders/AssetsLoader.hpp"

class Engine final
{
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Chunks> chunks;
    std::shared_ptr<LineBatch> lineBatch;
    
    AssetsLoader assets;

    ChunksRenderer chunksRenderer;

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