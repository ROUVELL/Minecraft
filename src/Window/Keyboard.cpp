#include "Keyboard.hpp"

#include <cstring>
#include <GLFW/glfw3.h>

#include "Window.hpp"


void keyCallback(GLFWwindow*, int key, int, int action, int);


unsigned int Keyboard::keys[1024];
unsigned int Keyboard::current = 0;

void Keyboard::initialize()
{
    memset(keys, 0, 1024 * sizeof(unsigned int));

 	glfwSetKeyCallback(Window::getInstance(), keyCallback);   
}

void keyCallback(GLFWwindow*, int key, int, int action, int)
{
	if (action == GLFW_PRESS)
		Keyboard::keys[key] = Keyboard::current;
	else if (action == GLFW_RELEASE)
		Keyboard::keys[key] = 0;
}