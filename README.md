# Crosshair
A Simple Crosshair made in opengl with glfw and imgui
# Space Invaders 

A C++20 project featuring a classic and simple crosshair, that can be modified with a ImGui menu, that saves data using a library for Json files.

## Features

- **Customizable Crosshair**: Adjust the color, size, and thickness of the crosshair.
- **Always-On-Top Overlay**: The crosshair window remains on top of all other windows.
- **Transparent Window**: The overlay is borderless and transparent, blending seamlessly with the desktop or game.
- **Real-Time Configuration**: Modify crosshair settings dynamically using a configuration menu.
- **Settings Persistence**: Save and load crosshair settings using a JSON file.
- ![C++](https://img.shields.io/badge/C%2B%2B-Standard-blue?logo=c%2B%2B&logoColor=white) ![GLFW](https://img.shields.io/badge/library-GLFW-blue?logo=glfw) ![nlohmann/json](https://img.shields.io/badge/json-nlohmann--json-yellow?logo=json) ![Dear ImGui](https://img.shields.io/badge/gui-Dear%20ImGui-lightgreen?logo=imgui) ![Windows](https://img.shields.io/badge/Platform-Windows-blue?logo=windows&logoColor=white)

## Getting Started

### Prerequisites

- C++20 compatible compiler (e.g., MSVC, GCC, Clang)
- [vcpkg](https://github.com/microsoft/vcpkg) for dependency management
- [Premake5](https://premake.github.io/) for project generation
- [Glfw](https://www.raylib.com/) (install via vcpkg)
- [ImGui](https://github.com/ocornut/imgui) (install via vcpkg)
- [Json](https://github.com/nlohmann/json) (install via vcpkg)
### Setup and Build Instructions

#### 1. Install Dependencies with vcpkg

Make sure you have [vcpkg](https://github.com/microsoft/vcpkg) installed and integrated with your compiler/IDE.

Install glfw, imgui and any other dependencies: vcpkg install imgui, glfw, nlohmann-json

#### 2. Generate Project Files with Premake5

This project uses [Premake5](https://premake.github.io/) to generate project files.

- Download Premake5 and place the executable in your PATH or project root.
- In the project root, run: premake5 vs2022

This will generate a Visual Studio 2022 solution. For other IDEs or build systems, use the appropriate Premake5 action (e.g., `premake5 gmake2` for GNU Makefiles).

#### 3. Build and Run

- Open the generated solution/project in your IDE (e.g., Visual Studio 2022).
- Build the project.
- Run the executable.

## Settings

- Color and size settings are saved in `CrosshairSettings.json`.
- Adjust the settings from the menu.

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.

---

*Made with glfw, imgui, nlohmann-json, vcpkg, Premake5, and C++20.*
