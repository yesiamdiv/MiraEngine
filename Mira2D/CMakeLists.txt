# Mira Engine - mira/CMakeLists.txt
# =================================
# This file builds the Mira Engine as a static library.


# --- Source File Collection ---
# Gather all .cpp files for compilation and .hpp files for the IDE.
# CONFIGURE_DEPENDS ensures CMake re-runs if you add/remove files.
file(GLOB_RECURSE MIRA_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE MIRA_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# --- Local Third-Party Libraries --------------------------------------------
# Automatically find and build any local libraries placed in the 'thirdparty' folder.
file(GLOB subdirectories CONFIGURE_DEPENDS "thirdparty/*")
foreach(subdirectory ${subdirectories})
    if(IS_DIRECTORY ${subdirectory} AND EXISTS "${subdirectory}/CMakeLists.txt")
        add_subdirectory(${subdirectory})
        # Note: You still need to manually link these below.
    endif()
endforeach()


# --- Mira Engine Target -----------------------------------------------------
# Create a static library target for the engine.
add_library(Mira2D STATIC ${MIRA_SOURCES})

# Add all source files from the src/ directory.
# file(GLOB_RECURSE MIRA_SOURCES "src/*.cpp")
target_sources(Mira2D PRIVATE ${MIRA_SOURCES} ${MIRA_HEADERS})

# Define public and private include directories.
target_include_directories(Mira2D
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/generated>
    PRIVATE
        src
)

# --- Library Linking ---
# NOTE: All remote dependencies (SDL, GLM, etc.) are now linked automatically
# by the mira_add_dependency() function in cmake/dependencies.cmake.
# We only need to link the local libraries found in our thirdparty folder here.
target_link_libraries(Mira2D PUBLIC
    glad # From the mira/thirdparty folder
)

# On Windows, we still need to link against OpenGL.
if(WIN32)
    target_link_libraries(Mira2D PUBLIC opengl32)
endif()

# --- Asset Handling for the Engine ---
file(COPY ${MIRA_ENGINE_ASSETS_DIR}/ DESTINATION ${MIRA_ASSETS_OUTPUT_DIR}/engine)

