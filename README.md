# MiraEngine 1.1

A simple 2D game engine and sample game project using CMake and SDL2.

---

## 📦 Project Structure

```
MiraEngine1.1/
├── Mira2D/         # Engine source code
├── game/           # Sample game using the engine
├── CMakeLists.txt  # Root CMake build script
└── README.md
```

---

## 🚀 Getting Started

### 1. **Clone the Repository**

```sh
git clone git@github.com:yesiamdiv/MiraEngine.git
cd MiraEngine1.1
```

### 2. **Install Prerequisites**

- **CMake** (version 3.15 or higher recommended)
- **C++ Compiler** (MSVC, GCC, or Clang)
- **Git**
- **Python** (optional, for some CMake features)
- **Windows:** Visual Studio 2019+ recommended

### 3. **Build the Project**

#### **Windows (Visual Studio)**
```sh
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release
```

#### **Linux/macOS**
```sh
mkdir build
cd build
cmake ..
make
```

### 4. **Run the Game**

- The built executable will be in `build/game/Release/` (Windows) or `build/game/` (Linux/macOS).

---

## 🛠️ Third-Party Dependencies

- **SDL2** and related libraries are managed and built automatically via CMake in `Mira2D/third_party`.
- No manual setup is required for dependencies.

---

## ⚙️ Customizing/Developing

- **Engine code:** `Mira2D/`
- **Game code:** `game/`
- Add your game source files to `game/src/` and headers to `game/include/`.

---

## 📝 Notes

- For custom SDL2 versions or additional dependencies, place archives in `Mira2D/third_party/sources/`.

---

## 🤝 Contributing

Pull requests and issues are welcome!

---

## 📄 License

MIT License (see `LICENSE` file for details)