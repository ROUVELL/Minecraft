#include "Engine.hpp"

#include <memory>
#include <sstream>

#include "Window/Window.hpp"
#include "Window/Events.hpp"
#include "Window/Camera.hpp"


Engine::Engine()
    : camera(std::make_shared<Camera>(glm::vec3(0.0, 60.0, 0.0), glm::radians(70.0f))),
    chunks(std::make_shared<Chunks>()),
    lineBatch(std::make_shared<LineBatch>()),
    chunksRenderer(chunks, lineBatch, camera),
    dt(16.6),
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

    glm::vec3 camPos = camera->getPosition();

    std::ostringstream title;
    title << "FPS: " << std::to_string((1.0 / dt));
    title << "  Position: [" << camPos.x << ", " << camPos.y << ", " << camPos.z << "]  ";
    Window::setTitle(title.str().c_str());
}

void Engine::processEvents()
{
    Events::pollEvents();

    if (Events::isJustPressed(KEY_ESCAPE))
        Window::close();
    if (Events::isJustPressed(KEY_TAB))
        Events::setCursorLock(!Events::isCursorLocked());
}

void Engine::update()
{
    if (Events::isCursorLocked())
    {
        camera->yaw(Events::getDx() * 0.2f * dt);
        camera->pitch(Events::getDy() * 0.1f * dt);

        glm::vec3 pos, norm, ipos;
        if (chunks->rayCast(camera->getPosition(), camera->getDirection(), &pos, &norm, &ipos))
        {
            if (Events::isJustClicked(MOUSE_BUTTON_LEFT))
            {
                glm::ivec3 voxelPos = ipos + norm;
                chunks->setVoxel(voxelPos.x, voxelPos.y, voxelPos.z, 1);
            }
            if (Events::isJustClicked(MOUSE_BUTTON_RIGHT))
                chunks->setVoxel((int)ipos.x, (int)ipos.y, (int)ipos.z, 0);

            chunksRenderer.drawVoxelNormal(ipos + 0.5f, norm);
            chunksRenderer.drawVoxelBox(ipos + 0.5f);
        }
    }

    static float speed = 30.0f;
    {
        if (Events::isPressed(KEY_W))
            camera->moveForward(dt * speed);
        if (Events::isPressed(KEY_S))
            camera->moveBackward(dt * speed);
        if (Events::isPressed(KEY_D))
            camera->moveRight(dt * speed);
        if (Events::isPressed(KEY_A))
            camera->moveLeft(dt * speed);
        if (Events::isPressed(KEY_SPACE))
            camera->moveUp(dt * speed);
        if (Events::isPressed(KEY_LEFT_SHIFT))
            camera->moveDown(dt * speed);
	}
    
    chunks->centeredAt(camera->getPosition().x, camera->getPosition().z);
    chunks->update();
}

void Engine::render()
{
    Window::clear();


    // chunksRenderer.drawChunkBox();
    chunksRenderer.drawWorldAxis();

    chunksRenderer.render(assets);
    lineBatch->render(assets, camera->getProjViewMatrix());

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