#pragma once

typedef unsigned int uint;

constexpr uint MOUSE_BUTTON_LEFT = 0;
constexpr uint MOUSE_BUTTON_RIGHT = 1;
constexpr uint MOUSE_BUTTON_MIDDLE = 2;

struct GLFWwindow;


class Mouse final
{
    static uint buttons[8];
	static uint current;

	static bool locked, started;

	static float dx, dy, x, y;

	Mouse() = default;
	~Mouse() = default;
	
	friend void mouseButtonCallback(GLFWwindow*, int button, int action, int);
	friend void cursorPositionCallback(GLFWwindow*, double xpos, double ypos);
	
public:
    static void initialize();
    static void update();

	static bool isCursorLocked() { return locked; }
	static bool isClicked(uint button);
	static bool isJustClicked(uint button);

	static float getDx() { return dx; }
	static float getDy() { return dy; }
	static float getX() { return x; }
	static float getY() { return y; }

	static void setCursorLock(bool flag);
};