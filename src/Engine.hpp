#pragma once

#include "World/Chunks.hpp"
#include "World/ChunksRenderer.hpp"
#include "World/Entity/Player.hpp"
#include "Loaders/AssetsLoader.hpp"
#include "Graphics/LineBatch.hpp"
#include "Graphics/TextBatch.hpp"

#include "Voxels/Atlas.hpp"


class Engine final
{
    Chunks chunks;
    Player player;
    ChunksRenderer chunksRenderer;

    LineBatch lineBatch;
    TextBatch textBatch;
    
    AssetsLoader assets;
    Atlas        atlas;

    f64 dt = 0.16;
    u32 fps = 60;

    void updateDt();
    void processEvents();
    void update();
    void render();

public:
    Engine();
    Engine(const Engine&) = delete;
    Engine(Engine&&) noexcept = delete;
    ~Engine() = default;

    f64 getDt() const    { return dt; }
    u32 getFps() const   { return fps; }

    void run();
    void stop();
};