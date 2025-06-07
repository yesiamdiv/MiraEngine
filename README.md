
---

# MiraEngine

A simple 2D game engine and sample game project built with CMake, SDL2, OpenGL (via GLAD), and GLM.

---

## 📦 Project Structure

```
MiraEngine1.1/
├── Mira2D/           #Engine source code, headers, assests etc.
├── game/             # Sample game source code, headers, assets etc.
├── CMakeLists.txt    # Root CMake build script
└── README.md
```

---

## Getting Started

### 1. **Clone the Repository**

```sh
git clone https://github.com/yesiamdiv/MiraEngine.git # Use HTTPS if SSH is not set up
cd MiraEngine
```

### 2. **Install Prerequisites**

-   **CMake** (version 3.15 or higher recommended)
-   **C++ Compiler** (MSVC for Windows; GCC or Clang for Linux/macOS)
-   **Git**
-   **Python** (optional, used by some CMake features)
-   **Windows:** Visual Studio 2019+ recommended (with "Desktop development with C++" workload).

### 3. **Build the Project**

MiraEngine uses **separate build directories for Debug and Release** configurations to ensure optimal performance for release builds and comprehensive debugging capabilities for development.

#### **Clean Previous Builds (Important!)**
If you're switching build strategies or configurations, it's best to remove old build directories first:
```sh
# From project root (MiraEngine/)
cmake -E remove_directory build_debug build_release
# Also remove any old 'build' directories if they exist
cmake -E remove_directory build
```

#### **Windows (Visual Studio)**

1.  **Configure for Debug:**
    ```sh
    mkdir build_debug
    cd build_debug
    cmake .. -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Debug
    ```
2.  **Build Debug:**
    ```sh
    cmake --build . --config Debug
    ```
3.  **Configure for Release:**
    ```sh
    cd .. # Go back to project root
    mkdir build_release
    cd build_release
    cmake .. -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Release
    ```
4.  **Build Release:**
    ```sh
    cmake --build . --config Release
    ```

#### **Linux/macOS**

1.  **Configure for Debug:**
    ```sh
    mkdir build_debug
    cd build_debug
    cmake .. -DCMAKE_BUILD_TYPE=Debug
    ```
2.  **Build Debug:**
    ```sh
    make -j$(nproc) # Use -j for parallel compilation (e.g., -j8 for 8 cores)
    ```
3.  **Configure for Release:**
    ```sh
    cd .. # Go back to project root
    mkdir build_release
    cd build_release
    cmake .. -DCMAKE_BUILD_TYPE=Release
    ```
4.  **Build Release:**
    ```sh
    make -j$(nproc)
    ```

### 4. **Run the Game**

After a successful build, the executable and its copied assets will be located within your chosen build directory.

#### **Run Debug Build:**
```sh
cd build_debug/game/
./MyGame # On Linux/macOS
MyGame.exe # On Windows
```

#### **Run Release Build:**
```sh
cd build_release/game/
./MyGame # On Linux/macOS
MyGame.exe # On Windows
```

---

##  Third-Party Dependencies

MiraEngine automatically handles its dependencies, so no manual setup is required:

* **SDL2**, **SDL2_image**, **SDL2_ttf**, **SDL2_mixer**: Built from source and installed into your specific build directory (`build_debug/Mira2D/third_party/` or `build_release/Mira2D/third_party/`).
* **GLAD**: Headers and source are integrated directly.
* **GLM**: Included as header-only.

---

## Asset Management

* **Game Assets:** Files in `game/assets/` are automatically copied to `[build_dir]/game/assets/`.
* **Engine Assets:** Files in `Mira2D/assets/` are automatically copied to `[build_dir]/game/engine_assets/`.

Your game executable expects to find these assets relative to its own location.

---

## Customizing/Developing

* **Engine Code:** Modify engine-level functionality in `Mira2D/`
* **Game Code:** Develop your game logic in `game/`
* Add your game source files to `game/src/` and headers to `game/include/`.
* Place custom engine assets (like shaders) in `Mira2D/assets/`.
* Place custom game assets (like images, sounds) in `game/assets/`.

---

## Notes

* For custom SDL2 versions or additional dependencies, place archives in `Mira2D/third_party/sources/`.

---

## Contributing

Pull requests and issues are welcome!

---

## 📄 License

MIT License (see `LICENSE` file for details)