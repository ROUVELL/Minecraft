#include "Events.hpp"

#include <cstring>
#include <GLFW/glfw3.h>

#include "Window.hpp"

void keyCallback(GLFWwindow*, int key, int, int action, int);
void mouseButtonCallback(GLFWwindow*, int button, int action, int);
void cursorPositionCallback(GLFWwindow*, double xpos, double ypos);
void windowSizeCallback(GLFWwindow*, int width, int height);
void windowFocusCallback(GLFWwindow*, int focused);

uint Events::_keys[1024];
uint Events::_buttons[8];
uint Events::_current = 0;
bool Events::_cursor_locked = false;
bool Events::_cursor_started = false;
float Events::deltaX = 0.0;
float Events::deltaY = 0.0;
float Events::x = 0.0;
float Events::y = 0.0;

void Events::initialize()
{
	memset(_keys, 0, 1024 * sizeof(uint));
	memset(_buttons, 0, 8 * sizeof(uint));

	glfwSetKeyCallback(Window::getInstance(), keyCallback);
	glfwSetMouseButtonCallback(Window::getInstance(), mouseButtonCallback);
	glfwSetCursorPosCallback(Window::getInstance(), cursorPositionCallback);
	glfwSetWindowSizeCallback(Window::getInstance(), windowSizeCallback);
	glfwSetWindowFocusCallback(Window::getInstance(), windowFocusCallback);
}

void Events::pollEvents()
{
	++_current;
	deltaX = 0.0;
	deltaY = 0.0;
	glfwPollEvents();
}

void Events::setCursorLock(bool flag)
{
	_cursor_locked = flag;
	Window::setCursorVisible(!_cursor_locked);
}

bool Events::isPressed(uint keycode)
{
	if (keycode >= 1024)
		return false;
	return _keys[keycode];
}

bool Events::isJustPressed(uint keycode)
{
	if (keycode >= 1024)
		return false;
	return _keys[keycode] == _current;
}

bool Events::isClicked(uint button)
{
	return _buttons[button];
}

bool Events::isJustClicked(uint button)
{
	return _buttons[button] == _current;
}

void keyCallback(GLFWwindow*, int key, int, int action, int)
{
	if (action == GLFW_PRESS)
		Events::_keys[key] = Events::_current;
	else if (action == GLFW_RELEASE)
		Events::_keys[key] = 0;
}

void mouseButtonCallback(GLFWwindow*, int button, int action, int)
{
	if (action == GLFW_PRESS)
		Events::_buttons[button] = Events::_current;
	else if (action == GLFW_RELEASE)
		Events::_buttons[button] = 0;
}

void cursorPositionCallback(GLFWwindow*, double xpos, double ypos)
{
	if (Events::_cursor_started)
	{
		Events::deltaX += xpos - Events::x;
		Events::deltaY += ypos - Events::y;
	}
	else
	{
		Events::_cursor_started = true;
	}

	Events::x = xpos;
	Events::y = ypos;
}

void windowSizeCallback(GLFWwindow*, int width, int height)
{
	Window::onSizeChanged(width, height);
}

void windowFocusCallback(GLFWwindow*, int focused)
{
	if (focused)
		Events::_cursor_started = false;
}












