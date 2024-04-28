#include "Keyboard.hpp"

#include <cstring>
#include <GLFW/glfw3.h>

#include "Window.hpp"


void keyCallback(GLFWwindow*, int key, int, int action, int);


uint Keyboard::keys[1024];
uint Keyboard::current = 0;

void Keyboard::initialize()
{
    memset(keys, 0, 1024 * sizeof(uint));

 	glfwSetKeyCallback(Window::getInstance(), keyCallback);   
}

void Keyboard::update()
{
    ++current;
}

bool Keyboard::isPressed(uint keycode)
{
	return keys[keycode];
}

bool Keyboard::isJustPressed(uint keycode)
{
	return keys[keycode] == current;
}

void keyCallback(GLFWwindow*, int key, int, int action, int)
{
	if (action == GLFW_PRESS)
		Keyboard::keys[key] = Keyboard::current;
	else if (action == GLFW_RELEASE)
		Keyboard::keys[key] = 0;
}