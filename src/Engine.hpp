#pragma once

#include "World/Chunk.hpp"
#include "World/ChunksRenderer.hpp"
#include "World/Entity/Player.hpp"
#include "Loaders/AssetsLoader.hpp"
#include "Graphics/LineBatch.hpp"
#include "Graphics/TextBatch.hpp"

#include "Voxels/Atlas.hpp"
#include <type_traits>

class Engine final
{
    Chunks chunks;
    Player player;
    ChunksRenderer chunksRenderer;

    LineBatch lineBatch;
    TextBatch textBatch;
    
    AssetsLoader assets;
    Atlas        atlas;

    double       dt;
    unsigned int fps;
    uint64_t     frame;

    void updateDt();
    void processEvents();
    void update();
    void render();

public:
    Engine();
    Engine(const Engine&) = delete;
    Engine(Engine&&) noexcept = delete;
    ~Engine() = default;

    double getDt() const        { return dt; }
    uint64_t getFrame() const   { return frame; }
    unsigned int getFps() const { return fps; }

    void run();
    void stop();
};