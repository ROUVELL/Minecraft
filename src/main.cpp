#include "Window/Window.hpp"
#include "Window/Events.hpp"
#include "Voxels/Blocks.hpp"
#include "Engine.hpp"

int main()
{
	Window::initialize(false, true);
	Events::initialize();
    Blocks::initialize();

    Engine engine;
	engine.run();

    Window::uninitialize();

    return 0;
}
