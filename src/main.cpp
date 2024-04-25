#include "Window/Window.hpp"
#include "Engine.hpp"

int main()
{
	Window::initialize(true, true);

    Engine engine;
	engine.run();

    Window::uninitialize();

    return 0;
}
