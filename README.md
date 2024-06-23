# Minecraft clone

### Docs
[English](docs/0.Home.md)


### Controls

- <kbd>**LMB**</kbd> - place block
- <kbd>**RMB**</kbd> - remove block
- <kbd>**W**</kbd> <kbd>**A**</kbd> <kbd>**S**</kbd> <kbd>**D**</kbd> - movement
- <kbd>**Space**</kbd> - move up
- <kbd>**CTRL**</kbd> - move down
- <kbd>**Shift**</kbd> - speed boost
- <kbd>**F5**</kbd> - clear the world


#### Arch-based distro:
If you use X11
```sh
sudo pacman -S glfw-x11 glew glm
```

If you use Wayland
```sh
sudo pacman -S glfw-wayland glew glm
```

#### Build with CMake
```sh
git clone --recursive https://github.com/ROUVELL/Minecraft.git
cd Minecraft
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```