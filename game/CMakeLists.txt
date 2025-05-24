# Define the project
project(MyGame)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the game source directory
set(GAME_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(GAME_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add game headers and sources
file(GLOB_RECURSE HEADER_FILES ${GAME_INCLUDE_DIR}/**.h)
file(GLOB_RECURSE SOURCE_FILES ${GAME_SRC_DIR}/**.cpp)

# Create the game executable
add_executable(MyGame ${SOURCE_FILES} ${HEADER_FILES} )

# Link the engine and dependencies
target_include_directories(MyGame PRIVATE 
    ${CMAKE_SOURCE_DIR}/game/include
    ${CMAKE_SOURCE_DIR}/Mira2D/include 
)
target_link_libraries(MyGame PRIVATE Mira2D)

# Ensure MyGame depends on Mira2D
add_dependencies(MyGame Mira2D)

set ( THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/Mira2D/third_party)
# Copy DLLs after build (Windows only)
# if(WIN32)
#     set(DLL_OUTPUT_DIR $<TARGET_FILE_DIR:MyGame>)  # Output to the same dir as MyGame.exe

#     add_custom_command(TARGET MyGame POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E copy_if_different
#             ${THIRD_PARTY_DIR}/SDL/lib/x64/SDL2.dll
#             ${THIRD_PARTY_DIR}/SDL_image/lib/x64/SDL2_image.dll
#             ${THIRD_PARTY_DIR}/SDL_ttf/lib/x64/SDL2_ttf.dll
#             ${THIRD_PARTY_DIR}/SDL_mixer/lib/x64/SDL2_mixer.dll
#             ${DLL_OUTPUT_DIR}
            
#         COMMENT "Copying SDL DLLs to the output directory"
#     )
# endif()
