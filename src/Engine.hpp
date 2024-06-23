#pragma once

#include "World/Chunks.hpp"
#include "World/ChunksRenderer.hpp"
#include "World/Entity/Player.hpp"
#include "Loaders/AssetsLoader.hpp"
#include "Graphics/LineBatch.hpp"
#include "Graphics/UIBatch.hpp"

#include "Voxels/Atlas.hpp"

#include "Gui/UIManager.hpp"


class Engine final
{
    Chunks chunks;
    Player player;
    ChunksRenderer chunksRenderer;

    LineBatch lineBatch;
    UIBatch uiBatch;
    UIManager uiManager;
    
    AssetsLoader assets;
    Atlas        atlas;

    f64 dt = 0.16;
    u32 fps = 60;

    void updateDt() noexcept;
    void processEvents() noexcept;
    void update() noexcept;
    void render() noexcept;

public:
    Engine() noexcept;
    Engine(const Engine&) = delete;
    Engine(Engine&&) noexcept = delete;
    ~Engine() = default;

    f64 getDt() const noexcept { return dt; }
    u32 getFps() const noexcept { return fps; }

    void run() noexcept;
    void stop() noexcept;
};