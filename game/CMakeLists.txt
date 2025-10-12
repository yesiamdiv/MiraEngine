# Mira Engine - game/CMakeLists.txt
# =================================
# This file builds the game executable.

# Create an executable target for the game.
add_executable(game)

# Add all game source files from the src/ directory.
file(GLOB_RECURSE GAME_SOURCES "src/*.cpp")
target_sources(game PRIVATE ${GAME_SOURCES})

# Define public and private include directories.
target_include_directories(game
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        src
)

# Link the game executable against the Mira Engine static library.
# This automatically brings in all of Mira's dependencies as well (like SDL2).
target_link_libraries(game PRIVATE Mira2D)

# Define the output directory for the executable.
set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# --- Asset Handling for the Game ---
# Copy game assets to the build output directory.
file(COPY ${MIRA_GAME_ASSETS_DIR}/ DESTINATION ${MIRA_ASSETS_OUTPUT_DIR}/game)

# --- Windows Specific: Copy DLLs ---
# On Windows, SDL2 and its libraries are built as shared libraries (.dll).
# This custom command runs after the build is finished and copies the necessary
# .dll files into the same directory as the game.exe so it can run.
if(WIN32)
    add_custom_command(
        TARGET game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL2::SDL2>"
            "$<TARGET_FILE_DIR:game>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL2_image::SDL2_image>"
            "$<TARGET_FILE_DIR:game>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL2_mixer::SDL2_mixer>"
            "$<TARGET_FILE_DIR:game>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL2_ttf::SDL2_ttf>"
            "$<TARGET_FILE_DIR:game>"
        COMMENT "Copying required SDL2 DLLs to executable directory..."
    )
endif()

