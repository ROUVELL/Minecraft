#pragma once

typedef unsigned int uint;

constexpr uint KEY_ESCAPE = 256;
constexpr uint KEY_TAB = 258;
constexpr uint KEY_SPACE = 32;
constexpr uint KEY_LEFT_SHIFT = 340;

constexpr uint KEY_W = 87;
constexpr uint KEY_S = 83;
constexpr uint KEY_A = 65;
constexpr uint KEY_D = 68;

constexpr uint KEY_UP = 265;
constexpr uint KEY_DOWN = 264;
constexpr uint KEY_LEFT = 263;
constexpr uint KEY_RIGHT = 262;

constexpr uint MOUSE_BUTTON_LEFT = 0;
constexpr uint MOUSE_BUTTON_RIGHT = 1;
constexpr uint MOUSE_BUTTON_MIDDLE = 2;

struct GLFWwindow;

class Events final
{
	static uint _keys[1024];
	static uint _buttons[8];
	static uint _current;

	static bool _cursor_locked;
	static bool _cursor_started;

	static float deltaX;
	static float deltaY;
	static float x;
	static float y;

	Events() = default;
	~Events() = default;

	friend void keyCallback(GLFWwindow*, int key, int, int action, int);
	friend void mouseButtonCallback(GLFWwindow*, int button, int action, int);
	friend void cursorPositionCallback(GLFWwindow*, double xpos, double ypos);
	friend void windowFocusCallback(GLFWwindow*, int focused);

public:
	static void initialize();
	static void pollEvents();
	static void setCursorLock(bool flag);

	static float getDx() { return deltaX; }
	static float getDy() { return deltaY; }
	static float getX() { return x; }
	static float getY() { return y; }
	static bool isCursorLocked() { return _cursor_locked; }

	static bool isPressed(uint keycode);
	static bool isJustPressed(uint keycode);
	static bool isClicked(uint button);
	static bool isJustClicked(uint button);
};

