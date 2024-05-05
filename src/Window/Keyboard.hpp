#pragma once

inline constexpr unsigned int KEY_ESCAPE = 256;
inline constexpr unsigned int KEY_TAB = 258;
inline constexpr unsigned int KEY_SPACE = 32;
inline constexpr unsigned int KEY_LEFT_SHIFT = 340;
inline constexpr unsigned int KEY_LEFT_CTRL = 341;

inline constexpr unsigned int KEY_0 = 48;
inline constexpr unsigned int KEY_1 = 49;
inline constexpr unsigned int KEY_2 = 50;
inline constexpr unsigned int KEY_3 = 51;
inline constexpr unsigned int KEY_4 = 52;
inline constexpr unsigned int KEY_5 = 53;
inline constexpr unsigned int KEY_6 = 54;
inline constexpr unsigned int KEY_7 = 55;
inline constexpr unsigned int KEY_8 = 56;
inline constexpr unsigned int KEY_9 = 57;

inline constexpr unsigned int KEY_W = 87;
inline constexpr unsigned int KEY_S = 83;
inline constexpr unsigned int KEY_A = 65;
inline constexpr unsigned int KEY_D = 68;

inline constexpr unsigned int KEY_UP = 265;
inline constexpr unsigned int KEY_DOWN = 264;
inline constexpr unsigned int KEY_LEFT = 263;
inline constexpr unsigned int KEY_RIGHT = 262;

struct GLFWwindow;

class Keyboard final
{
	static unsigned int keys[1024];
    static unsigned int current;

    Keyboard() = default;
    ~Keyboard() = default;

    friend void keyCallback(GLFWwindow*, int key, int, int action, int);

public:
	static void initialize();
    static void update() { ++current; }

    static bool isPressed(unsigned int keycode)     { return keys[keycode]; }
	static bool isJustPressed(unsigned int keycode) { return keys[keycode] == current; }
};