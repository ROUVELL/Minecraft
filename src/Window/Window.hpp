#pragma once

struct GLFWwindow;

class Window final
{
	static GLFWwindow* window;
	static int width, height;
	static float pixelWidth, pixelHeight;

	Window() = default;
	~Window() = default;

public:

	static bool isOpen();

	static GLFWwindow* getInstance() { return window; }
	static int getWidth() { return width; }
	static int getHeight() { return height; }
	static float getAspect() { return (float)width / (float)height; }
	static float getPixelWidth() { return pixelWidth; }
	static float getPixelHeight() { return pixelHeight; }
	static double getTime();

	static void setCursorVisible(bool flag);
	static void setTitle(const char* title);

	static void onSizeChanged(int width, int height);

	static void initialize(bool fullscreen, bool vsync);
	static void uninitialize();

	static void clear();
	static void pollEvents();
	static void swapBuffers();
	static void close();

};
