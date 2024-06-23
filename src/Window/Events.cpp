#include "Events.hpp"

#include <cstring>
#include <iostream>

#include <GLFW/glfw3.h>

#include "Window.hpp"


void keyCallback(GLFWwindow*, int key, int, int action, int mods) noexcept;
void textCallback(GLFWwindow*, unsigned int codepoint) noexcept;
void mouseButtonCallback(GLFWwindow*, int button, int action, int mods) noexcept;
void cursorPositionCallback(GLFWwindow*, double xpos, double ypos) noexcept;


u32 Events::keys[1024];
u32 Events::buttons[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
u32 Events::current = 0;
f32 Events::x = 0.0f;
f32 Events::y = 0.0f;
f32 Events::dx = 0.0f;
f32 Events::dy = 0.0f;
bool Events::locked = false;
std::queue<event_t> Events::_queue;

void Events::initialize() noexcept
{
    memset(keys, 0, 1024 * sizeof(u32));

    glfwSetKeyCallback(Window::getInstance(), keyCallback); 
    glfwSetMouseButtonCallback(Window::getInstance(), mouseButtonCallback);
	glfwSetCursorPosCallback(Window::getInstance(), cursorPositionCallback);
    glfwSetCharCallback(Window::getInstance(), textCallback);
}

void Events::setCursorLock(bool flag) noexcept
{
    locked = flag;
    Window::setCursorVisible(!locked);
}


void keyCallback(GLFWwindow*, int key, int, int action, int mods) noexcept
{
	if (action == GLFW_PRESS)
    {
        Events::keys[key] = Events::current;
        Events::_queue.push(event_t{ .type = EventType::KEY_PRESSED, .key = (u32)key, .mods = (u32)mods });
    }
	else if (action == GLFW_RELEASE)
	{
        Events::keys[key] = 0;
        Events::_queue.push(event_t{ .type = EventType::KEY_RELEASED, .key = (u32)key, .mods = (u32)mods });
    }
}

void textCallback(GLFWwindow*, unsigned int codepoint) noexcept
{
    if (codepoint < 256)
        Events::_queue.push(event_t{ .type = EventType::TEXT_ENTER, .codepoint = codepoint });
}

void mouseButtonCallback(GLFWwindow*, int button, int action, int mods) noexcept
{
	if (action == GLFW_PRESS)
	{
        Events::buttons[button] = Events::current;
        Events::_queue.push(event_t{ .type = EventType::MOUSE_BUTTON_PRESSED, .mods = (u32)mods, .button = (u32)button, .x = Events::x, .y = Events::y });
    }
	else if (action == GLFW_RELEASE)
	{
        Events::buttons[button] = 0;
        Events::_queue.push(event_t{ .type = EventType::MOUSE_BUTTON_RELEASED, .mods = (u32)mods, .button = 0, .x = Events::x, .y = Events::y });
    }
}

void cursorPositionCallback(GLFWwindow*, double xpos, double ypos) noexcept
{
	static bool started = false;

	if (started)
	{
		Events::dx += xpos - Events::x;
		Events::dy += ypos - Events::y;
	}
	else
		started = true;

	Events::x = xpos;
	Events::y = ypos;

    if (started)
        Events::_queue.push(event_t{ .type = EventType::MOUSE_MOVED, .x = Events::x, .y = Events::y });
}