-----

# Mira Engine

Welcome to the Mira Engine\! This is a 2D game engine project built with C++, CMake, SDL2, and OpenGL.

This repository is structured to support both engine development and game development simultaneously. The build system is designed to be easy to use, automatically handling the download and compilation of all required third-party libraries.

-----

## 📦 Project Structure

```
mira-engine/
├── .gitignore
├── CMakeLists.txt            # The root CMake file (set your game name here)
├── README.md
│
├── cmake/
│   └── dependencies.cmake    # *** SINGLE-FILE-EDIT for remote libraries ***
│
├── mira/
│   ├── CMakeLists.txt        # Engine's build script
│   ├── assets/               # Engine-specific assets (shaders, default fonts)
│   ├── include/              # Engine headers
│   ├── src/                  # Engine source code
│   └── thirdparty/           # Drop pre-downloaded engine libraries here (e.g., GLAD)
│
└── sandbox/                  # Your game project folder (can be renamed)
    ├── CMakeLists.txt        # Game's build script
    ├── assets/               # Game-specific assets (images, sounds)
    ├── include/              # Game headers
    ├── src/                  # Game source code
    └── thirdparty/           # Drop pre-downloaded game-specific libraries here
```

-----

## 🚀 Getting Started

Follow these steps to clone, configure, and build the project.

### 1\. Prerequisites

First, ensure you have the necessary tools installed:

  * **CMake** (version 3.15 or higher recommended)
  * **C++ Compiler** (MSVC for Windows; GCC or Clang for Linux/macOS)
  * **Git**
  * **Windows:** Visual Studio 2019+ with the "Desktop development with C++" workload is recommended.

### 2\. Clone the Repository

```sh
git clone https://github.com/yesiamdiv/MiraEngine.git
cd mira-engine
```

### 3\. Set Up Your Game Project

1.  **Rename the `sandbox/` folder** to your desired game name (e.g., `MyAwesomeGame/`).

2.  Open the **root `CMakeLists.txt`** file and change the `GAME_PROJECT_NAME` variable to match your new folder name:

    ```cmake
    # Change "sandbox" to your new name
    set(GAME_PROJECT_NAME "MyAwesomeGame")
    ```

### 4\. Build Instructions

You can use any CMake-compatible build system or IDE (like Visual Studio, VS Code with CMake Tools, or CLion).

#### **Command Line (All Platforms)**

The first time you build, CMake will download and compile all dependencies, which may take a few minutes.

1.  **Configure:**

    ```sh
    # For a Debug build (recommended for development)
    cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug

    # For a Release build (optimized for performance)
    cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
    ```

2.  **Build:**

    ```sh
    cmake --build build
    ```

#### **Platform-Specific Notes**

  * **Windows**: The command-line instructions above work perfectly, especially with Visual Studio's build tools.
  * **Linux/macOS**: You may need to install system-level development libraries for dependencies like SDL2. Scripts are provided for convenience.
    1.  Make the installation script executable:
        ```sh
        # For Debian/Ubuntu-based systems
        chmod +x scripts/install_dependencies_apt.sh
        # For Fedora/CentOS-based systems
        chmod +x scripts/install_dependencies_dnf.sh
        ```
    2.  Run the appropriate script:
        ```sh
        # This will prompt for your sudo password
        ./scripts/install_dependencies_apt.sh
        ```

### 5\. Run the Game

The executable will be located in the `build/bin` directory.

```sh
# On Windows
./build/bin/MyAwesomeGame.exe

# On Linux/macOS
./build/bin/MyAwesomeGame
```

-----

## 🧩 Dependency & Asset Management

### How to Add Third-Party Libraries

The process for adding libraries is now extremely streamlined.

#### **Method 1: Automatic Download (Recommended)**

This is the best method for any library available on Git.

1.  **Open `cmake/dependencies.cmake`**: This is the only file you need to edit.
2.  **Add your library**: Call the `mira_add_dependency()` function with the library's information.

**Example: Adding a logging library to the *engine***

```cmake
mira_add_dependency(spdlog            # The library's target name
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        v1.14.1
    TARGETS        Mira2d             # <-- Automatically links to the mira engine
)
```

**Example: Adding a networking library only to the *game***

```cmake
# Note: Use your game's name (e.g., MyAwesomeGame) as the target
mira_add_dependency(enet
    GIT_REPOSITORY https://github.com/lsalzman/enet.git
    GIT_TAG        v1.3.17
    TARGETS        MyAwesomeGame     # <-- Automatically links to the game
)
```

#### **Method 2: Local Libraries**

This method is ideal for libraries you've downloaded manually or for generated code like GLAD.

1.  **Place the library**: Copy the library's source folder into either `mira/thirdparty/` or `MyAwesomeGame/thirdparty/`.
2.  **Manually link it**: Open the corresponding `CMakeLists.txt` (`mira/` or `MyAwesomeGame/`) and add the library's target name to the `target_link_libraries()` call.

### Asset Management

The build system automatically copies asset files to the output directory.

  * **Engine Assets**: Files in `mira/assets/` are copied to `build/bin/assets/`.
  * **Game Assets**: Files in `MyAwesomeGame/assets/` are copied to `build/bin/assets/`.

Your game executable expects to find these assets in a relative `assets/` folder.

-----

## 🤝 Contributing

Pull requests and issues are welcome\!

-----

## 📄 License

This project is licensed under the MIT License. See the `LICENSE` file for details.