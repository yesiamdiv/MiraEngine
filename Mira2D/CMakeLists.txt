# Mira Engine - mira/CMakeLists.txt
# =================================
# This file builds the Mira Engine as a static library.

# --- Local Third-Party Libraries --------------------------------------------
# Add pre-downloaded libraries from the thirdparty folder.
# This makes them available as targets to link against.
add_subdirectory(thirdparty/glad)


# --- Mira Engine Target -----------------------------------------------------
# Create a static library target for the engine.
add_library(Mira2D STATIC)

# Add all source files from the src/ directory.
file(GLOB_RECURSE MIRA_SOURCES "src/*.cpp")
target_sources(Mira2D PRIVATE ${MIRA_SOURCES})

# Define public and private include directories.
target_include_directories(Mira2D
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        # Add the generated files directory to the include path
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/generated>
    PRIVATE
        src
)

# Link the engine against its dependencies.
# We link against 'glad' which we added via add_subdirectory.
target_link_libraries(Mira2D PUBLIC
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
    SDL2_ttf::SDL2_ttf
    glm::glm
    glad
)

# On Windows, we need to link against OpenGL. On other systems, SDL handles this.
if(WIN32)
    target_link_libraries(Mira2D PUBLIC opengl32)
endif()

# --- Asset Handling for the Engine ---
# Copy engine assets to the build output directory.
# This ensures they are available when running the built executable.
file(COPY ${MIRA_ENGINE_ASSETS_DIR}/ DESTINATION ${MIRA_ASSETS_OUTPUT_DIR}/engine)

