#pragma once

#include <queue>

#include "../typedefs.hpp"


struct GLFWwindow;


enum class EventType
{
    KEY_PRESSED,
    KEY_RELEASED,
    MOUSE_BUTTON_PRESSED,
    MOUSE_BUTTON_RELEASED,
    MOUSE_MOVED,
    TEXT_ENTER
};

struct event_t
{
    EventType type;
    u32 key = 0;
    u32 mods = 0;
    u32 codepoint = 0;
    u32 button = 0;
    f32 x = 0;
    f32 y = 0;
};

class Events
{
    static u32 keys[1024];
    static u32 buttons[8];
	static u32 current;

	static f32 x, y, dx, dy;
	static bool locked;

    Events() = default;
    ~Events() = default;

    friend void keyCallback(GLFWwindow*, int key, int, int action, int mods) noexcept;
    friend void textCallback(GLFWwindow*, unsigned int codepoint) noexcept;
    friend void mouseButtonCallback(GLFWwindow*, int button, int action, int mods) noexcept;
	friend void cursorPositionCallback(GLFWwindow*, double xpos, double ypos) noexcept;

public:
    static std::queue<event_t> _queue;

    static void initialize() noexcept;
    static void _update() noexcept { ++current; dx = dy = 0.0f; }

    static bool pressed(unsigned int keycode) noexcept     { return keys[keycode]; }
	static bool justPressed(unsigned int keycode) noexcept { return keys[keycode] == current; }
	static bool clicked(unsigned int button) noexcept      { return buttons[button]; }
	static bool justClicked(unsigned int button) noexcept  { return buttons[button] == current; }
    static bool cursorLocked() noexcept                    { return locked; }

	static f32 getDx() noexcept { return dx; }
	static f32 getDy() noexcept { return dy; }
	static f32 getX() noexcept  { return x; }
	static f32 getY() noexcept  { return y; }

    static void setCursorLock(bool flag) noexcept;
};