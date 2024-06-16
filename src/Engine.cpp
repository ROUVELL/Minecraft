#include "Engine.hpp"

#include <sstream>

#include "World/Raycasting.hpp"
#include "Voxels/Blocks.hpp"
#include "Window/Window.hpp"
#include "Window/Keyboard.hpp"
#include "Window/Mouse.hpp"
#include "Gui/Label.hpp"


Engine::Engine()
    : player(&chunks, glm::vec3(8.5f, 10.0f, 8.5f), 5.0f),
    chunksRenderer(&chunks, &lineBatch, player.getCamera())
{
    Mouse::setCursorLock(true);
    
    Blocks::initialize(atlas);
}

void Engine::updateDt()
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

void Engine::processEvents()
{
    Window::pollEvents();

    if (Keyboard::isJustPressed(KEY_ESCAPE))
        Window::close();
    if (Keyboard::isJustPressed(KEY_TAB))
        Mouse::setCursorLock(!Mouse::isCursorLocked());
}

void Engine::update()
{
    Raycasting::rayCast(player.getCamera()->getPosition(), player.getCamera()->getDirection(), &chunks);
    player.update(dt);
    
    chunks.centeredAt(player.getCamera()->getPosition().x, player.getCamera()->getPosition().z);
    chunks.update();
}

void Engine::render()
{
    Window::clear();

    glm::vec3 camPos = player.getCamera()->getPosition();

    std::ostringstream title;
    title << "FPS: " << fps << '\n';
    title << "Position: [" << camPos.x << ", " << camPos.y << ", " << camPos.z << "]\n";
    title << "Angle: [yaw: " << player.getCamera()->getYawAngle() << ", pitch: " << player.getCamera()->getPitchAgnle() << "]\n";
    title << "Look at: " << Blocks::getBlock(Raycasting::id).name;
    title << "\nSelected: " << Blocks::getBlock(player.getSelected()).name;
    
    static Label lbl(&textBatch, title.str(), 3, 0);
    lbl.setText(title.str());
    lbl.render();

    if (Raycasting::id)
    {
        chunksRenderer.drawVoxelNormal(Raycasting::iend, Raycasting::norm);
        chunksRenderer.drawVoxelBox(Raycasting::iend);
    }

    // chunksRenderer.drawChunkBox();
    chunksRenderer.drawWorldAxis();
    chunksRenderer.render(assets, atlas);

    // player hitbox
    // lineBatch.box(player.getCamera()->getPosition() - glm::vec3{0.2f, 1.6f, 0.2f}, glm::vec3{0.4f, 1.7f, 0.4f}, {0.0f, 1.0f, 0.0f, 1.0f});

    lineBatch.render(assets, player.getCamera()->getProjViewMatrix());
    textBatch.render(assets);

    Window::swapBuffers();
}

void Engine::run()
{
    while (Window::isOpen())
    {
        updateDt();
        processEvents();
        update();
        render();
    }
}

void Engine::stop()
{
    Window::close();
}