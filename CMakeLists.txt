cmake_minimum_required(VERSION 3.10)
project(Mira2DProject)

add_subdirectory(Mira2D)
add_subdirectory(game)

# Ensure MyGame is built after Mira2D
add_dependencies(MyGame Mira2D)

# target_compile_definitions(MyGame PUBLIC ASSET_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
