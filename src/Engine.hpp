#pragma once

#include "World/Chunk.hpp"
#include "World/ChunksRenderer.hpp"
#include "World/Entity/Player.hpp"
#include "Loaders/AssetsLoader.hpp"
#include "Graphics/LineBatch.hpp"
#include "Graphics/TextBatch.hpp"

class Engine final
{
    Chunks chunks;
    Player player;
    ChunksRenderer chunksRenderer;

    LineBatch lineBatch;
    TextBatch textBatch;
    
    AssetsLoader assets;

    double dt;
    unsigned int fps;
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
    unsigned int getFps() const { return fps; }

    void run();
    void stop();
};