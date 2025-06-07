cmake_minimum_required(VERSION 3.15)
project(Mira2D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/Mira2D/third_party)
# Define where the source archives are (remains in the source tree)
set(SOURCES_DIR ${CMAKE_SOURCE_DIR}/Mira2D/third_party/sources)

include(ExternalProject)

# Helper to build SDL libs from local source archive
function(build_sdl_lib name archive_name extra_args)
    set(ARCHIVE_PATH ${SOURCES_DIR}/${archive_name})
    
    # Define the installation base directory for external projects relative to the current binary dir (e.g., build_debug/ or build_release/)
    set(EXTERNAL_INSTALL_BASE_DIR ${CMAKE_BINARY_DIR}/Mira2D/third_party)

    # The actual install directory for this specific SDL library
    set(INSTALL_DIR ${EXTERNAL_INSTALL_BASE_DIR}/${name})
    
    # The prefix for ExternalProject's internal build directory (also within the build dir)
    set(EXTERNAL_PREFIX_DIR ${EXTERNAL_INSTALL_BASE_DIR}/${name}_prefix)

    if(NOT name STREQUAL "SDL")
        # These arguments need to point to SDL's installation within *this* specific build directory's 
        set(SDL2_DIR_ARG -DSDL2_DIR=${EXTERNAL_INSTALL_BASE_DIR}/SDL)
        set(PREFIX_PATH_ARG -DCMAKE_PREFIX_PATH=${EXTERNAL_INSTALL_BASE_DIR}/SDL)
    else()
        set(SDL2_DIR_ARG "")
        set(PREFIX_PATH_ARG "")
    endif()

    ExternalProject_Add(
        ${name}
        URL ${ARCHIVE_PATH}
        DOWNLOAD_EXTRACT_TIMESTAMP true
        PREFIX ${EXTERNAL_PREFIX_DIR} # ExternalProject's internal build directory
        CMAKE_ARGS
            -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR} # Where SDL installs its headers/libs
            -DBUILD_SHARED_LIBS=OFF
            ${SDL2_DIR_ARG}
            ${PREFIX_PATH_ARG}
            ${extra_args}
        -DCMAKE_BUILD_TYPE=$<CONFIG>
    )
endfunction()

# Download and build SDL libraries (Windows / Linux)
if(WIN32)
    build_sdl_lib(SDL SDL2-2.30.10.zip "")
    build_sdl_lib(SDL_image SDL2_image-2.8.4.zip "-DSDL2IMAGE_VENDORED=ON -DSDL2IMAGE_DOWNLOAD_DEPENDENCIES=ON")
    build_sdl_lib(SDL_ttf SDL2_ttf-2.24.0.zip "-DSDL2TTF_VENDORED=ON -DSDL2TTF_DOWNLOAD_DEPENDENCIES=ON")
    build_sdl_lib(SDL_mixer SDL2_mixer-2.8.1.zip "")
else() # Assume Linux for other platforms or can add specific checks like APPLE for macOS
    build_sdl_lib(SDL SDL2-2.30.10.tar.gz "")
    build_sdl_lib(SDL_image SDL2_image-2.8.4.tar.gz "-DSDL2IMAGE_VENDORED=ON -DSDL2IMAGE_DOWNLOAD_DEPENDENCIES=ON")
    build_sdl_lib(SDL_ttf SDL2_ttf-2.24.0.tar.gz "-DSDL2TTF_VENDORED=ON -DSDL2TTF_DOWNLOAD_DEPENDENCIES=ON")
    build_sdl_lib(SDL_mixer SDL2_mixer-2.8.1.tar.gz "")
endif()

# Define the EXTERNAL_INSTALL_BASE_DIR for use outside the function scope
set(EXTERNAL_INSTALL_BASE_DIR ${CMAKE_BINARY_DIR}/Mira2D/third_party)

# # Set include/library paths to the build output
# set(SDL_INCLUDE_DIR ${EXTERNAL_INSTALL_BASE_DIR}/SDL/include/SDL2)

# Use generator expressions for configuration-specific AND platform-specific library names
# Now all paths use EXTERNAL_INSTALL_BASE_DIR
if(WIN32)
    # Windows naming conventions (e.g., SDL2-staticd.lib)
    set(SDL_LIBRARY
        $<$<CONFIG:Debug>:${EXTERNAL_INSTALL_BASE_DIR}/SDL/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2-staticd${CMAKE_STATIC_LIBRARY_SUFFIX}>
        $<$<CONFIG:Release>:${EXTERNAL_INSTALL_BASE_DIR}/SDL/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2-static${CMAKE_STATIC_LIBRARY_SUFFIX}>
        $<$<NOT:$<CONFIG:Debug>>:$<$<NOT:$<CONFIG:Release>>:${EXTERNAL_INSTALL_BASE_DIR}/SDL/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2-static${CMAKE_STATIC_LIBRARY_SUFFIX}>>
    )
    set(SDL_MAIN_LIBRARY
        $<$<CONFIG:Debug>:${EXTERNAL_INSTALL_BASE_DIR}/SDL/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2maind${CMAKE_STATIC_LIBRARY_SUFFIX}>
        $<$<CONFIG:Release>:${EXTERNAL_INSTALL_BASE_DIR}/SDL/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2main${CMAKE_STATIC_LIBRARY_SUFFIX}>
        $<$<NOT:$<CONFIG:Debug>>:$<$<NOT:$<CONFIG:Release>>:${EXTERNAL_INSTALL_BASE_DIR}/SDL/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2main${CMAKE_STATIC_LIBRARY_SUFFIX}>>
    )
    set(SDL_IMAGE_LIBRARY
        $<$<CONFIG:Debug>:${EXTERNAL_INSTALL_BASE_DIR}/SDL_image/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_image-staticd${CMAKE_STATIC_LIBRARY_SUFFIX}>
        $<$<CONFIG:Release>:${EXTERNAL_INSTALL_BASE_DIR}/SDL_image/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_image-static${CMAKE_STATIC_LIBRARY_SUFFIX}>
        $<$<NOT:$<CONFIG:Debug>>:$<$<NOT:$<CONFIG:Release>>:${EXTERNAL_INSTALL_BASE_DIR}/SDL_image/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_image-static${CMAKE_STATIC_LIBRARY_SUFFIX}>>
    )
    set(SDL_TTF_LIBRARY
        $<$<CONFIG:Debug>:${EXTERNAL_INSTALL_BASE_DIR}/SDL_ttf/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_ttfd${CMAKE_STATIC_LIBRARY_SUFFIX}>
        $<$<CONFIG:Release>:${EXTERNAL_INSTALL_BASE_DIR}/SDL_ttf/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_ttf${CMAKE_STATIC_LIBRARY_SUFFIX}>
        $<$<NOT:$<CONFIG:Debug>>:$<$<NOT:$<CONFIG:Release>>:${EXTERNAL_INSTALL_BASE_DIR}/SDL_ttf/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_ttf${CMAKE_STATIC_LIBRARY_SUFFIX}>>
    )
    set(SDL_MIXER_LIBRARY
        $<$<CONFIG:Debug>:${EXTERNAL_INSTALL_BASE_DIR}/SDL_mixer/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_mixer-staticd${CMAKE_STATIC_LIBRARY_SUFFIX}>
        $<$<CONFIG:Release>:${EXTERNAL_INSTALL_BASE_DIR}/SDL_mixer/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_mixer-static${CMAKE_STATIC_LIBRARY_SUFFIX}>
        $<$<NOT:$<CONFIG:Debug>>:$<$<NOT:$<CONFIG:Release>>:${EXTERNAL_INSTALL_BASE_DIR}/SDL_mixer/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_mixer-static${CMAKE_STATIC_LIBRARY_SUFFIX}>>
    )
else() # Linux (and other non-Windows platforms)
    # Linux naming conventions based on your observed output (e.g., libSDL2d.a)
    set(SDL_LIBRARY
        $<$<CONFIG:Debug>:${EXTERNAL_INSTALL_BASE_DIR}/SDL/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2d${CMAKE_STATIC_LIBRARY_SUFFIX}>
        $<$<CONFIG:Release>:${EXTERNAL_INSTALL_BASE_DIR}/SDL/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2${CMAKE_STATIC_LIBRARY_SUFFIX}>
        $<$<NOT:$<CONFIG:Debug>>:$<$<NOT:$<CONFIG:Release>>:${EXTERNAL_INSTALL_BASE_DIR}/SDL/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2${CMAKE_STATIC_LIBRARY_SUFFIX}>>
    )
    set(SDL_MAIN_LIBRARY
        $<$<CONFIG:Debug>:${EXTERNAL_INSTALL_BASE_DIR}/SDL/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2maind${CMAKE_STATIC_LIBRARY_SUFFIX}>
        $<$<CONFIG:Release>:${EXTERNAL_INSTALL_BASE_DIR}/SDL/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2main${CMAKE_STATIC_LIBRARY_SUFFIX}>
        $<$<NOT:$<CONFIG:Debug>>:$<$<NOT:$<CONFIG:Release>>:${EXTERNAL_INSTALL_BASE_DIR}/SDL/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2main${CMAKE_STATIC_LIBRARY_SUFFIX}>>
    )
    set(SDL_IMAGE_LIBRARY
        $<$<CONFIG:Debug>:${EXTERNAL_INSTALL_BASE_DIR}/SDL_image/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_imaged${CMAKE_STATIC_LIBRARY_SUFFIX}>
        $<$<CONFIG:Release>:${EXTERNAL_INSTALL_BASE_DIR}/SDL_image/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_image${CMAKE_STATIC_LIBRARY_SUFFIX}>
        $<$<NOT:$<CONFIG:Debug>>:$<$<NOT:$<CONFIG:Release>>:${EXTERNAL_INSTALL_BASE_DIR}/SDL_image/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_image${CMAKE_STATIC_LIBRARY_SUFFIX}>>
    )
    set(SDL_TTF_LIBRARY
        $<$<CONFIG:Debug>:${EXTERNAL_INSTALL_BASE_DIR}/SDL_ttf/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_ttfd${CMAKE_STATIC_LIBRARY_SUFFIX}>
        $<$<CONFIG:Release>:${EXTERNAL_INSTALL_BASE_DIR}/SDL_ttf/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_ttf${CMAKE_STATIC_LIBRARY_SUFFIX}>
        $<$<NOT:$<CONFIG:Debug>>:$<$<NOT:$<CONFIG:Release>>:${EXTERNAL_INSTALL_BASE_DIR}/SDL_ttf/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_ttf${CMAKE_STATIC_LIBRARY_SUFFIX}>>
    )
    set(SDL_MIXER_LIBRARY
        $<$<CONFIG:Debug>:${EXTERNAL_INSTALL_BASE_DIR}/SDL_mixer/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_mixerd${CMAKE_STATIC_LIBRARY_SUFFIX}>
        $<$<CONFIG:Release>:${EXTERNAL_INSTALL_BASE_DIR}/SDL_mixer/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_mixer${CMAKE_STATIC_LIBRARY_SUFFIX}>
        $<$<NOT:$<CONFIG:Debug>>:$<$<NOT:$<CONFIG:Release>>:${EXTERNAL_INSTALL_BASE_DIR}/SDL_mixer/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_mixer${CMAKE_STATIC_LIBRARY_SUFFIX}>>
    )
endif()

# Add engine headers and sources
file(GLOB_RECURSE HEADER_FILES "include/**/*.h")
file(GLOB_RECURSE SOURCE_FILES "src/**/*.cpp")

# Create Mira2D library
add_library(Mira2D STATIC ${HEADER_FILES} ${SOURCE_FILES} )

# Include GLAD (source files included)
# This will be inside the main build directory too: build_debug/glad/
add_subdirectory(${THIRD_PARTY_DIR}/glad)

target_include_directories(Mira2D SYSTEM PUBLIC
    ${CMAKE_SOURCE_DIR}/Mira2D/include
    ${CMAKE_SOURCE_DIR}/Mira2D/third_party/glad/include
    ${CMAKE_SOURCE_DIR}/Mira2D/third_party/glm 
    ${EXTERNAL_INSTALL_BASE_DIR}/SDL/include/SDL2
    ${EXTERNAL_INSTALL_BASE_DIR}/SDL_image/include/SDL2
    ${EXTERNAL_INSTALL_BASE_DIR}/SDL_mixer/include/SDL2
    ${EXTERNAL_INSTALL_BASE_DIR}/SDL_ttf/include/SDL2
)

target_link_libraries(Mira2D PRIVATE
    glad
    ${SDL_LIBRARY}
    ${SDL_MAIN_LIBRARY}
    ${SDL_IMAGE_LIBRARY}
    ${SDL_TTF_LIBRARY}
    ${SDL_MIXER_LIBRARY}
)

if(WIN32)
    target_link_libraries(Mira2D PRIVATE
        winmm
        imm32
        version
        setupapi
        cfgmgr32
    )
endif()

# Ensure SDL dependencies are built before Mira2D
add_dependencies(Mira2D SDL SDL_image SDL_ttf SDL_mixer)

set(SDL_TTF_EXTRA_ARGS -DSDL2TTF_VENDORED=ON -DSDL2TTF_DOWNLOAD_DEPENDENCIES=ON)





