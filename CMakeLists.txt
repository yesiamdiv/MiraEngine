# Mira Engine Project - Root CMakeLists.txt
# ==========================================
# This file manages the entire project using a Fetch-Define-Link strategy.

cmake_minimum_required(VERSION 3.15)

# --- Game Project Configuration ---
set(GAME_PROJECT_NAME "sandbox" CACHE STRING "The name of the game project folder and executable")
project(${GAME_PROJECT_NAME} VERSION 0.1.0 LANGUAGES CXX)

# --- Standard C++ and Module Setup ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# ===================================================================
# THE BUILD ORCHESTRATION
# ===================================================================

# First, include the dependency file to make our custom functions available.
include(dependencies)

# STEP 1: FETCH FIRST
# This registers, downloads, and prepares all remote dependency targets.
mira_fetch_all_dependencies()

# --- Asset Management ---
# This can be configured now that the project is set up.
set(MIRA_ENGINE_ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Mira2D/assets)
set(MIRA_GAME_ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${GAME_PROJECT_NAME}/assets)
set(MIRA_ASSETS_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/assets)

# Generate a header file with the asset path for C++ code to use.
# set(MIRA_PATHS_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/Mira2D/include/Utils/paths.hpp)
set(MIRA_PATHS_HEADER ${CMAKE_BINARY_DIR}/generated/paths.hpp)
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Mira2D/include/Utils/paths.hpp.in
    ${MIRA_PATHS_HEADER}
)

# STEP 2: DEFINE TARGETS
# Now we define our own project targets ('Mira2D' and the game).
# They can now be found by the linking function.
add_subdirectory(Mira2D)
add_subdirectory(${GAME_PROJECT_NAME})

# STEP 3: LINK LAST
# With both dependency targets and our project targets available,
# we can finally link them together.
mira_link_all_dependencies()
# ===================================================================




