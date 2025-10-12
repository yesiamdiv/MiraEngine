# Mira Engine Project - Root CMakeLists.txt
# ==========================================
# This file manages the entire project, including fetching dependencies
# and adding the engine and game subdirectories.

cmake_minimum_required(VERSION 3.15)
project(MiraEngine VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Dependency Management --------------------------------------------------
# We use FetchContent to download and build third-party libraries automatically.
# This avoids needing users to install them manually.
include(FetchContent)

# SDL2
FetchContent_Declare(
  SDL
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-2.30.0
)

# SDL2_image
FetchContent_Declare(
  SDL_image
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
  GIT_TAG release-2.8.0
)

# SDL2_mixer
FetchContent_Declare(
  SDL_mixer
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
  GIT_TAG release-2.8.0
)

# SDL2_ttf
FetchContent_Declare(
  SDL_ttf
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
  GIT_TAG release-2.22.0
)

# GLM (OpenGL Mathematics)
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 0.9.9.8
)

# Make dependencies available
FetchContent_MakeAvailable(SDL SDL_image SDL_mixer SDL_ttf glm)

# --- Asset Management -------------------------------------------------------
# Define a variable for the absolute path to the assets in the source directory.
set(MIRA_ENGINE_ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Mira2D/assets)
set(MIRA_GAME_ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/game/assets)

# Define the output directory for assets in the build folder.
set(MIRA_ASSETS_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/assets)

# Generate a header file with the asset path for C++ code to use.
# This makes finding assets robust and independent of the working directory.
set(MIRA_PATHS_HEADER ${CMAKE_CURRENT_BINARY_DIR}/generated/Mira2D/paths.hpp)
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Mira2D/include/config/paths.hpp.in
    ${MIRA_PATHS_HEADER}
)

# --- Project Subdirectories -------------------------------------------------
# Add the engine and game projects. CMake will find their respective
# CMakeLists.txt files and process them.
add_subdirectory(Mira2D)
add_subdirectory(game)
