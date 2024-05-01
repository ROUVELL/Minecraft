#include "Window/Window.hpp"
#include "Voxels/Blocks.hpp"
#include "Engine.hpp"

int main()
{
	Window::initialize(true, true);
    Blocks::initialize();

    Engine engine;
	engine.run();

    Window::uninitialize();

    return 0;
}
