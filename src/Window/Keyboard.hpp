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

struct GLFWwindow;


class Keyboard final
{
	static uint keys[1024];
    static uint current;

    Keyboard() = default;
    ~Keyboard() = default;

    friend void keyCallback(GLFWwindow*, int key, int, int action, int);

public:
	static void initialize();
    static void update();

    static bool isPressed(uint keycode);
	static bool isJustPressed(uint keycode);
};