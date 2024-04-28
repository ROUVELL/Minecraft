#include "Mouse.hpp"

#include <cstring>
#include <GLFW/glfw3.h>

#include "Window.hpp"

void mouseButtonCallback(GLFWwindow*, int button, int action, int);
void cursorPositionCallback(GLFWwindow*, double xpos, double ypos);

uint Mouse::buttons[8];
uint Mouse::current = 0;
bool Mouse::locked = false;
bool Mouse::started = false;
float Mouse::dx = 0.0;
float Mouse::dy = 0.0;
float Mouse::x = 0.0;
float Mouse::y = 0.0;


void Mouse::initialize()
{
    memset(buttons, 0, 8 * sizeof(uint));

	glfwSetMouseButtonCallback(Window::getInstance(), mouseButtonCallback);
	glfwSetCursorPosCallback(Window::getInstance(), cursorPositionCallback);
}

void Mouse::update()
{
    dx = dy = 0.0;
    ++current;
}

bool Mouse::isClicked(uint button)
{
	return buttons[button];
}

bool Mouse::isJustClicked(uint button)
{
	return buttons[button] == current;
}

void Mouse::setCursorLock(bool flag)
{
    locked = flag;
    Window::setCursorVisible(!locked);
}


void mouseButtonCallback(GLFWwindow*, int button, int action, int)
{
	if (action == GLFW_PRESS)
		Mouse::buttons[button] = Mouse::current;
	else if (action == GLFW_RELEASE)
		Mouse::buttons[button] = 0;
}

void cursorPositionCallback(GLFWwindow*, double xpos, double ypos)
{
	if (Mouse::started)
	{
		Mouse::dx += xpos - Mouse::x;
		Mouse::dy += ypos - Mouse::y;
	}
	else
		Mouse::started = true;

	Mouse::x = xpos;
	Mouse::y = ypos;
}