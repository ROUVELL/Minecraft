#include "Engine.hpp"

#include <sstream>

#include "World/Raycasting.hpp"
#include "Voxels/Blocks.hpp"
#include "Window/Window.hpp"
#include "Window/Events.hpp"
#include "Window/keys.hpp"

#include "Gui/UIManager.hpp"
#include "Gui/Elements/Label.hpp"


Engine::Engine() noexcept
    : player(&chunks, glm::vec3(8.5f, 10.0f, 8.5f), 5.0f),
    chunksRenderer(&chunks, &lineBatch, player.getCamera()),
    uiManager(&uiBatch)
{
    Events::setCursorLock(true);
    
    Blocks::initialize(atlas);
}

void Engine::updateDt() noexcept
{
    static double lastTime = 0.0;

    double currTime = Window::getTime();
    dt = currTime - lastTime;
    lastTime = currTime;

    static double lastUpdate = 0.0;
    if (currTime - lastUpdate > 0.2)
    {
        lastUpdate = currTime;
        fps = static_cast<u32>(1.0 / dt);
    }
}

void Engine::processEvents() noexcept
{
    Window::pollEvents();

    if (Events::justPressed(KEY_ESCAPE))
        Window::close();
    if (Events::justPressed(KEY_TAB))
        Events::setCursorLock(!Events::cursorLocked());

    uiManager.process_input();
}

void Engine::update() noexcept
{
    Raycasting::rayCast(player.getCamera()->getPosition(), player.getCamera()->getDirection(), &chunks);
    player.update(dt);
    
    chunks.centeredAt(player.getCamera()->getPosition().x, player.getCamera()->getPosition().z);
    chunks.update();
}

void Engine::render() noexcept
{
    Window::clear();

    glm::vec3 camPos = player.getCamera()->getPosition();

    std::ostringstream title;
    title << "FPS: " << fps << "\n\n";
    title << "Position: [" << camPos.x << ", " << camPos.y << ", " << camPos.z << "]\n";
    title << "Angle: [yaw: " << player.getCamera()->getYawAngle() << ", pitch: " << player.getCamera()->getPitchAgnle() << "]\n\n";
    title << "Look at: " << Blocks::getBlock(Raycasting::id).name;
    title << "\nSelected: " << Blocks::getBlock(player.getSelected()).name;
    
    static Label lbl;
    lbl.setPosition({ 3, 0 });
    lbl.setText(title.str());


    if (Raycasting::id)
    {
        // chunksRenderer.drawVoxelNormal(Raycasting::iend, Raycasting::norm);
        chunksRenderer.drawVoxelBox(Raycasting::iend);
    }

    // chunksRenderer.drawChunkBox();
    // chunksRenderer.drawWorldAxis();
    chunksRenderer.render(assets, atlas);

    const int hw = Window::getWidth() / 2;
    const int hh = Window::getHeight() / 2;

    uiBatch.line(hw, hh - 10, hw, hh + 10, color_t{225, 150});
    uiBatch.line(hw - 10, hh, hw + 10, hh, color_t{255, 150});

    // player hitbox
    // lineBatch.box(player.getCamera()->getPosition() - glm::vec3{0.2f, 1.6f, 0.2f}, glm::vec3{0.4f, 1.7f, 0.4f}, {0.0f, 1.0f, 0.0f, 1.0f});

    lineBatch.render(assets, player.getCamera()->getProjViewMatrix());

    uiManager.render(assets);

    Window::swapBuffers();
}

void Engine::run() noexcept
{
    while (Window::isOpen())
    {
        updateDt();
        processEvents();
        update();
        render();
    }
}

void Engine::stop() noexcept
{
    Window::close();
}