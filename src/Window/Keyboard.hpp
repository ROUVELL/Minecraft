#pragma once

using uint = unsigned int;

inline constexpr uint KEY_ESCAPE = 256;
inline constexpr uint KEY_TAB = 258;
inline constexpr uint KEY_SPACE = 32;
inline constexpr uint KEY_LEFT_SHIFT = 340;
inline constexpr uint KEY_LEFT_CTRL = 341;

inline constexpr uint KEY_0 = 48;
inline constexpr uint KEY_1 = 49;
inline constexpr uint KEY_2 = 50;
inline constexpr uint KEY_3 = 51;
inline constexpr uint KEY_4 = 52;
inline constexpr uint KEY_5 = 53;
inline constexpr uint KEY_6 = 54;
inline constexpr uint KEY_7 = 55;
inline constexpr uint KEY_8 = 56;
inline constexpr uint KEY_9 = 57;

inline constexpr uint KEY_W = 87;
inline constexpr uint KEY_S = 83;
inline constexpr uint KEY_A = 65;
inline constexpr uint KEY_D = 68;

inline constexpr uint KEY_UP = 265;
inline constexpr uint KEY_DOWN = 264;
inline constexpr uint KEY_LEFT = 263;
inline constexpr uint KEY_RIGHT = 262;

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