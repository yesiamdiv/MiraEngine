cmake_minimum_required(VERSION 3.10)
project(Mira2DProject)

add_subdirectory(Mira2D)
add_subdirectory(game)

# Ensure MyGame is built after Mira2D
add_dependencies(MyGame Mira2D)

# Asset path handling based on build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "")
    # Development paths (absolute)
    file(TO_NATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/game/Assets" GAME_ASSET_PATH)
    file(TO_NATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Mira2D/Assets" MIRA2D_ASSET_PATH)
    
    target_compile_definitions(MyGame PUBLIC ASSET_PATH="${GAME_ASSET_PATH}")
    target_compile_definitions(Mira2D PUBLIC ASSET_PATH="${MIRA2D_ASSET_PATH}")
    
    message(STATUS "Using absolute asset paths for development")
else()
    # Release paths (relative)
    target_compile_definitions(MyGame PUBLIC ASSET_PATH="./Assets")
    target_compile_definitions(Mira2D PUBLIC ASSET_PATH="./Assets")
    
    message(STATUS "Using relative asset paths for release")
endif()

# Define the asset path macros properly with quotes to avoid syntax errors
target_compile_definitions(MyGame PUBLIC "GET_ASSET_PATH(file)=ASSET_PATH \"/\" file")
target_compile_definitions(Mira2D PUBLIC "GET_ASSET_PATH(file)=ASSET_PATH \"/\" file")
