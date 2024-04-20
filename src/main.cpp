#include "Window/Window.hpp"
#include "Window/Events.hpp"
#include "Engine.hpp"

int main()
{
	Window::initialize(false, false);
	Events::initialize();

    Engine engine;
	engine.run();

    Window::uninitialize();

    return 0;
}
