# MiraEngine 1.1

A simple 2D game engine and sample game project using CMake and SDL2.

---

## 📦 Project Structure

```
MiraEngine/
├── Mira2D/           # Engine source code
├── game/             # Sample game using the engine
├── CMakeLists.txt    # Root CMake build script
└── README.md
```

---

## 🚀 Getting Started

### 1. **Clone the Repository**

First things first, get a copy of the project on your machine:

```sh
git clone git@github.com:yesiamdiv/MiraEngine.git
cd MiraEngine
```

### 2. **Install Prerequisites**

You'll need a few tools installed on your system:

* **CMake**: Version **3.15 or higher** is required.
* **C++ Compiler**: A modern C++ compiler like **MSVC** (on Windows), **GCC**, or **Clang**.
* **Git**: For cloning the repository.
* **Python**: (Optional) Sometimes used by CMake for internal scripts.

---

### 3. **Build the Project**

We'll use CMake to build the project. The commands differ slightly based on your operating system and whether you want a **Debug** or **Release** build.

#### **Linux/macOS**

On Unix-like systems, it's common to create separate build directories for Debug and Release builds.

1.  **For a Debug Build:**
    ```sh
    # Navigate to the project root
    cd MiraEngine

    # Create and configure the build directory for Debug
    cmake -S . -B build_debug -DCMAKE_BUILD_TYPE=Debug

    # Build the project (this will use your system's 'make')
    cmake --build build_debug
    ```

2.  **For a Release Build:**
    ```sh
    # Navigate to the project root
    cd MiraEngine

    # Create and configure the build directory for Release
    cmake -S . -B build_release -DCMAKE_BUILD_TYPE=Release

    # Build the project
    cmake --build build_release
    ```

#### **Windows (Visual Studio)**

On Windows with Visual Studio, CMake creates a single solution file that can handle both Debug and Release builds.

1.  **Configure the Project:**
    Open a **"Developer Command Prompt for VS"** (search for it in your Start Menu) or a terminal configured with your VS environment. Then, run:

    ```cmd
    # Navigate to the project root
    cd C:\path\to\MiraEngine

    # Create and configure the build directory (CMake auto-detects your VS version)
    cmake -S . -B build_vs
    ```

2.  **Build (Choose your method):**

    * **Option A: Build within Visual Studio (Recommended for development)**
        * Open the generated solution file: `build_vs/Mira2DProject.sln`
        * In Visual Studio, select your desired configuration (e.g., **"Debug"** or **"Release"**) from the dropdown menu in the toolbar.
        * Build the solution (e.g., `Build > Build Solution` or press `F7`).

    * **Option B: Build from the Command Line:**
        ```cmd
        # For a Debug Build
        cmake --build build_vs --config Debug

        # For a Release Build
        cmake --build build_vs --config Release
        ```

---

### 4. **Run the Game**

After building, you'll find the executable in a specific location:

* **Linux/macOS:**
    * **Debug:** `build_debug/game/MyGame`
    * **Release:** `build_release/game/MyGame`
* **Windows:**
    * **Debug:** `build_vs/game/Debug/MyGame.exe`
    * **Release:** `build_vs/game/Release/MyGame.exe`

---

## 🛠️ Third-Party Dependencies

* **SDL2** and its extensions (SDL_image, SDL_ttf, SDL_mixer) are managed and built automatically by CMake.
* You don't need to manually install any of these dependencies; the build process handles it.

---

## ⚙️ Customizing/Developing

* **Engine code:** Found in the `Mira2D/` directory.
* **Game code:** Found in the `game/` directory.
* To add your own game logic, place source files in `game/src/` and headers in `game/include/`.

---

## 📝 Notes

* If you need to use custom versions of SDL2 or add other dependencies, place their source archives (e.g., `.zip`, `.tar.gz`) into the `Mira2D/third_party/sources/` directory.

---

## 🤝 Contributing

Pull requests and issues are always welcome! Feel free to contribute to MiraEngine.

---

## 📄 License

This project is licensed under the MIT License. See the `LICENSE` file for full details.
