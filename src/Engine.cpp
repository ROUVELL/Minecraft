#include "Engine.hpp"

#include <sstream>
#include <string>

#include "Window/Window.hpp"
#include "Window/Keyboard.hpp"
#include "Window/Mouse.hpp"
#include "Gui/Label.hpp"


Engine::Engine()
    : camera(glm::vec3(0.0, 60.0, 0.0), 70.0f),
    chunksRenderer(&chunks, &lineBatch, &camera),
    dt(16.6),
    fps(60),
    frame(0)
{
}

Engine::~Engine()
{
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
        fps = static_cast<unsigned int>(1.0 / dt);
    }

    glm::vec3 camPos = camera.getPosition();

    std::ostringstream title;
    title << "FPS: " << fps << '\n';
    title << "Position: [" << camPos.x << ", " << camPos.y << ", " << camPos.z << "]\n";
    
    static Label lbl(&textBatch, title.str(), 3, 0);
    lbl.setText(title.str());
    lbl.render();
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
    if (Mouse::isCursorLocked())
    {
        camera.yaw(-Mouse::getDx() * 0.2f * dt);
        camera.pitch(-Mouse::getDy() * 0.1f * dt);

        glm::vec3 pos, norm, ipos;
        if (chunks.rayCast(camera.getPosition(), camera.getDirection(), &pos, &norm, &ipos))
        {
            if (Mouse::isJustClicked(MOUSE_BUTTON_LEFT))
            {
                glm::ivec3 voxelPos = ipos + norm;
                chunks.setVoxel(voxelPos.x, voxelPos.y, voxelPos.z, 1);
            }
            if (Mouse::isJustClicked(MOUSE_BUTTON_RIGHT))
                chunks.setVoxel((int)ipos.x, (int)ipos.y, (int)ipos.z, 0);

            chunksRenderer.drawVoxelNormal(ipos + 0.5f, norm);
            chunksRenderer.drawVoxelBox(ipos + 0.5f);
        }
    }

    static float speed = 30.0f;
    {
        if (Keyboard::isPressed(KEY_W))
            camera.moveForward(dt * speed);
        if (Keyboard::isPressed(KEY_S))
            camera.moveBackward(dt * speed);
        if (Keyboard::isPressed(KEY_D))
            camera.moveRight(dt * speed);
        if (Keyboard::isPressed(KEY_A))
            camera.moveLeft(dt * speed);
        if (Keyboard::isPressed(KEY_SPACE))
            camera.moveUp(dt * speed);
        if (Keyboard::isPressed(KEY_LEFT_SHIFT))
            camera.moveDown(dt * speed);
	}
    
    chunks.centeredAt(camera.getPosition().x, camera.getPosition().z);
    chunks.update();
}

void Engine::render()
{
    Window::clear();

    // chunksRenderer.drawChunkBox();
    chunksRenderer.drawWorldAxis();
    chunksRenderer.render(assets);

    lineBatch.render(assets, camera.getProjViewMatrix());
    textBatch.render(assets);

    Window::swapBuffers();
}

void Engine::run()
{
    while (Window::isOpen())
    {
        ++frame;

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