#include "Window/Window.hpp"
#include "Window/Events.hpp"
#include "Engine.hpp"

int main()
{
	Window::initialize(true, true);
	Events::initialize();

    Engine engine;
	engine.run();

    Window::uninitialize();

    return 0;
}
