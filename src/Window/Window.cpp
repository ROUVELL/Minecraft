#include "Window.hpp"

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Keyboard.hpp"
#include "Mouse.hpp"


void windowSizeCallback(GLFWwindow*, int width, int height);


GLFWwindow* Window::window = nullptr;
int Window::width = 1920;
int Window::height = 1020;
float Window::pixelWidth = 2.0f / Window::width;
float Window::pixelHeight = 2.0f / Window::height;

bool Window::isOpen()
{
	return !glfwWindowShouldClose(window);
}

double Window::getTime()
{
	return glfwGetTime();
}

void Window::setCursorVisible(bool flag)
{
	glfwSetInputMode(window, GLFW_CURSOR, flag ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

void Window::setTitle(const char* title)
{
	glfwSetWindowTitle(window, title);
}

void Window::onSizeChanged(int width, int height)
{
	glViewport(0, 0, width, height);

	Window::width = width;
	Window::height = height;
	Window::pixelWidth = 2.0 / width;
	Window::pixelHeight = 2.0 / height;
}

void Window::initialize(bool fullscreen, bool vsinc)
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW!\n";
        return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	if (fullscreen)
		window = glfwCreateWindow(width, height, "Voxel Engine", glfwGetPrimaryMonitor(), nullptr);
	else
    	window = glfwCreateWindow(width, height, "Voxel Engine", nullptr, nullptr);

    if (window == nullptr)
    {
		std::cerr << "Failed to open window!\n";
        glfwTerminate();
        return;
    }

	Keyboard::initialize();
	Mouse::initialize();

	glfwSetWindowSizeCallback(Window::getInstance(), windowSizeCallback);

    glfwSwapInterval(vsinc ? 1 : 0);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
    	std::cerr << "Failed to initialize GLEW!\n";
    	uninitialize();
    	return;
    }

	glViewport(0, 0, width, height);

    glClearColor(0.4, 0.4, 0.4, 1.0);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	// glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(2.0f);
}

void Window::uninitialize()
{
	close();
	glfwTerminate();
}

void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::pollEvents()
{
	Keyboard::_update();
	Mouse::_update();
	glfwPollEvents();
}

void Window::swapBuffers()
{
	glfwSwapBuffers(window);
}

void Window::close()
{
	glfwSetWindowShouldClose(window, true);
}


void windowSizeCallback(GLFWwindow*, int width, int height)
{
	Window::onSizeChanged(width, height);
}