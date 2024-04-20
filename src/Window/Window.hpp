#pragma once

struct GLFWwindow;

class Window final
{
	static GLFWwindow* window;
	static int width, height;

	Window() = default;
	~Window() = default;

public:

	static bool isOpen();

	static GLFWwindow* getInstance() { return window; }
	static int getWidth() { return width; }
	static int getHeight() { return height; }
	static float getAspect() { return (float)width / (float)height; } 
	static double getTime();

	static void setCursorVisible(bool flag);
	static void setTitle(const char* title);

	static void onSizeChanged(int newWidth, int newHeight);

	static void initialize(bool fullscreen, bool vsync);
	static void uninitialize();
	static void clear();
	static void swapBuffers();
	static void close();

};
