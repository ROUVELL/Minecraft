#include "Engine.hpp"

#include <sstream>

#include "Window/Window.hpp"
#include "Window/Events.hpp"
#include "Graphics/Shader.hpp"
#include "Window/Camera.hpp"

const glm::vec4 BLOCK_BOX_COLOR = glm::vec4(1.0, 1.0, 1.0, 0.6);
const glm::vec4 RED = glm::vec4(1.0, 0.0, 0.0, 1.0);
const glm::vec4 GREEN = glm::vec4(0.0, 1.0, 0.0, 1.0);
const glm::vec4 BLUE = glm::vec4(0.0, 0.0, 1.0, 1.0);
const glm::vec4 BLACK = glm::vec4(0.0, 0.0, 0.0, 1.0);


Engine::Engine()
    : camera(glm::vec3(0.0, 60.0, 0.0), glm::radians(70.0f)),
    dt(16.6),
    frame(0)
{
    shaders["chunk"] = loadShader("../res/shaders/main.glslv", "../res/shaders/main.glslf");
    textures["chunk"] = loadTexture("../res/textures/grass.png");
}

Engine::~Engine()
{
    for (auto& shader : shaders)
        shader.second.del();

    for (auto& texture : textures)
        texture.second.del();
}

void Engine::updateDt()
{
    static double lastTime = 0.0;

    double currTime = Window::getTime();
    dt = currTime - lastTime;
    lastTime = currTime;

    glm::vec3 camPos = camera.getPosition();

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
        camera.yaw(Events::getDx() * 0.2f * dt);
        camera.pitch(Events::getDy() * 0.1f * dt);

        glm::vec3 pos, norm, ipos;
        if (chunks.rayCast(camera.getPosition(), camera.getDirection(), &pos, &norm, &ipos))
        {
            if (Events::isJustClicked(MOUSE_BUTTON_LEFT))
            {
                glm::ivec3 voxelPos = ipos + norm;
                chunks.setVoxel(voxelPos.x, voxelPos.y, voxelPos.z, 1);
            }
            if (Events::isJustClicked(MOUSE_BUTTON_RIGHT))
                chunks.setVoxel((int)ipos.x, (int)ipos.y, (int)ipos.z, 0);

            lineBatch.line(ipos + 0.5f, ipos + 0.5f + norm, BLACK);
            lineBatch.box(ipos + 0.5f, glm::vec3(1.01f), BLOCK_BOX_COLOR);
        }
    }

    static float speed = 30.0f;
    {
        if (Events::isPressed(KEY_W))
            camera.moveForward(dt * speed);
        if (Events::isPressed(KEY_S))
            camera.moveBackward(dt * speed);
        if (Events::isPressed(KEY_D))
            camera.moveRight(dt * speed);
        if (Events::isPressed(KEY_A))
            camera.moveLeft(dt * speed);
        if (Events::isPressed(KEY_SPACE))
            camera.moveUp(dt * speed);
        if (Events::isPressed(KEY_LEFT_SHIFT))
            camera.moveDown(dt * speed);
	}
    
    glm::vec lookAt = camera.getPosition() + camera.getDirection();
    lineBatch.line(lookAt, lookAt + glm::vec3(0.15, 0.0, 0.0), RED);
    lineBatch.line(lookAt, lookAt + glm::vec3(0.0, 0.15, 0.0), GREEN);
    lineBatch.line(lookAt, lookAt + glm::vec3(0.0, 0.0, 0.15), BLUE);

    // int cx = (int)camera.position.x / CHUNK_SIDE;
    // int cz = (int)camera.position.z / CHUNK_SIDE;
    // if (camera.position.x < 0.0f) --cx;
    // if (camera.position.z < 0.0f) --cz;

    // float x = cx * CHUNK_SIDE + (CHUNK_SIDE * 0.5f);
    // float z = cz * CHUNK_SIDE + (CHUNK_SIDE * 0.5f);

    // lineBatch.box(glm::vec3(x, CHUNK_HEIGHT * 0.5f, z), glm::vec3(CHUNK_SIDE, CHUNK_HEIGHT, CHUNK_SIDE) + 0.01f);

    chunks.centeredAt(camera.getPosition().x, camera.getPosition().z);
    chunks.update();
}

void Engine::render()
{
    Window::clear();

    shaders["chunk"].use();
    shaders["chunk"].uniformMatrix("projview", camera.getProjViewMatrix());
    textures["chunk"].bind();

    chunks.render(shaders["chunk"]);
    lineBatch.render(camera.getProjViewMatrix());

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