#pragma once

inline constexpr unsigned int MOUSE_BUTTON_LEFT = 0;
inline constexpr unsigned int MOUSE_BUTTON_RIGHT = 1;
inline constexpr unsigned int MOUSE_BUTTON_MIDDLE = 2;

struct GLFWwindow;

class Mouse final
{
    static unsigned int buttons[8];
	static unsigned int current;

	static bool locked, started;

	static float dx, dy, x, y;

	Mouse() = default;
	~Mouse() = default;
	
	friend void mouseButtonCallback(GLFWwindow*, int button, int action, int);
	friend void cursorPositionCallback(GLFWwindow*, double xpos, double ypos);
	
public:
    static void initialize();
    static void _update() { dx = dy = 0; ++current; }

	static bool isCursorLocked()                   { return locked; }
	static bool isClicked(unsigned int button)     { return buttons[button]; }
	static bool isJustClicked(unsigned int button) { return buttons[button] == current; }

	static float getDx() { return dx; }
	static float getDy() { return dy; }
	static float getX()  { return x; }
	static float getY()  { return y; }

	static void setCursorLock(bool flag);
};