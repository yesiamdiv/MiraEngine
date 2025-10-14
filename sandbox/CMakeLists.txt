# Mira Engine - Game Project CMakeLists.txt
# =========================================
# This file builds the game executable. It's a generic template
# that uses the GAME_PROJECT_NAME variable from the root CMake file.

# --- Local Third-Party Libraries for the Game ---
# Automatically find and build any local libraries specific to this game.
file(GLOB subdirectories CONFIGURE_DEPENDS "thirdparty/*")
foreach(subdirectory ${subdirectories})
    if(IS_DIRECTORY ${subdirectory} AND EXISTS "${subdirectory}/CMakeLists.txt")
        add_subdirectory(${subdirectory})
        # Note: You still need to manually link these below.
    endif() 
endforeach()

# Create an executable target for the game using the custom name.
add_executable(${GAME_PROJECT_NAME})

# Add all game source files from the src/ directory.
file(GLOB_RECURSE GAME_SOURCES "src/*.cpp")
target_sources(${GAME_PROJECT_NAME} PRIVATE ${GAME_SOURCES})

# Define public and private include directories.
target_include_directories(${GAME_PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        src
)

# Link the game executable against the Mira Engine static library.
# If you add a game-specific library to the thirdparty folder, link it here.
target_link_libraries(${GAME_PROJECT_NAME} PRIVATE 
    Mira2D
)

# Define the output directory for the executable.
set_target_properties(${GAME_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# --- Asset Handling for the Game ---
file(COPY ${MIRA_GAME_ASSETS_DIR}/ DESTINATION ${MIRA_ASSETS_OUTPUT_DIR}/game)

# --- Windows Specific: Copy DLLs ---
if(WIN32)
    add_custom_command(
        TARGET ${GAME_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL2::SDL2>"
            "$<TARGET_FILE_DIR:${GAME_PROJECT_NAME}>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL2_image::SDL2_image>"
            "$<TARGET_FILE_DIR:${GAME_PROJECT_NAME}>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL2_mixer::SDL2_mixer>"
            "$<TARGET_FILE_DIR:${GAME_PROJECT_NAME}>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL2_ttf::SDL2_ttf>"
            "$<TARGET_FILE_DIR:${GAME_PROJECT_NAME}>"
        COMMENT "Copying required SDL2 DLLs to executable directory..."
    )
endif()
