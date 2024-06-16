#include "Mouse.hpp"

#include <GLFW/glfw3.h>

#include "Window.hpp"

void mouseButtonCallback(GLFWwindow*, int button, int action, int);
void cursorPositionCallback(GLFWwindow*, double xpos, double ypos);

unsigned int Mouse::buttons[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
unsigned int Mouse::current = 0;
bool Mouse::locked = false;
float Mouse::dx = 0.0;
float Mouse::dy = 0.0;
float Mouse::x = 0.0;
float Mouse::y = 0.0;


void Mouse::initialize()
{
	glfwSetMouseButtonCallback(Window::getInstance(), mouseButtonCallback);
	glfwSetCursorPosCallback(Window::getInstance(), cursorPositionCallback);
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
	static bool started = false;

	if (started)
	{
		Mouse::dx += xpos - Mouse::x;
		Mouse::dy += ypos - Mouse::y;
	}
	else
		started = true;

	Mouse::x = xpos;
	Mouse::y = ypos;
}