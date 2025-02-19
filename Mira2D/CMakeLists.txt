cmake_minimum_required(VERSION 3.15)
project(Mira2D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set third-party directory
set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/Mira2D/third_party)

include(ExternalProject)

# Function to download SDL libraries only if they are missing
function(download_sdl_lib name url)
    set(SOURCE_PATH ${THIRD_PARTY_DIR}/${name})

    if(NOT EXISTS ${SOURCE_PATH})
        message(STATUS "Downloading ${name} from ${url}...")
        ExternalProject_Add(
            ${name}
            URL ${url}
            DOWNLOAD_EXTRACT_TIMESTAMP true
            SOURCE_DIR ${SOURCE_PATH}
            CONFIGURE_COMMAND ""
            BUILD_COMMAND ""
            INSTALL_COMMAND ""
            BUILD_IN_SOURCE 1
        )
    else()
        message(STATUS "${name} already exists. Skipping download.")
        add_custom_target(${name} ALL COMMENT "${name} is already present in ${SOURCE_PATH}")
    endif()
endfunction()

# Download SDL libraries (Windows / Linux)
if(WIN32)
    download_sdl_lib(SDL https://www.libsdl.org/release/SDL2-devel-2.30.10-VC.zip)
    download_sdl_lib(SDL_image https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.8.4-VC.zip)
    download_sdl_lib(SDL_ttf https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.24.0-VC.zip)
    download_sdl_lib(SDL_mixer https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.8.1-VC.zip)

    set(SDL_INCLUDE_DIR ${THIRD_PARTY_DIR}/SDL/include)
    set(SDL_LIBRARY ${THIRD_PARTY_DIR}/SDL/lib/x64/SDL2.lib)
    set(SDL_MAIN_LIBRARY ${THIRD_PARTY_DIR}/SDL/lib/x64/SDL2main.lib)
    set(SDL_IMAGE_LIBRARY ${THIRD_PARTY_DIR}/SDL_image/lib/x64/SDL2_image.lib)
    set(SDL_TTF_LIBRARY ${THIRD_PARTY_DIR}/SDL_ttf/lib/x64/SDL2_ttf.lib)
    set(SDL_MIXER_LIBRARY ${THIRD_PARTY_DIR}/SDL_mixer/lib/x64/SDL2_mixer.lib)

else()
    download_sdl_lib(SDL https://www.libsdl.org/release/SDL2-2.30.10.tar.gz)
    download_sdl_lib(SDL_image https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.8.4.tar.gz)
    download_sdl_lib(SDL_ttf https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.24.0.tar.gz)
    download_sdl_lib(SDL_mixer https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.8.1.tar.gz)

    set(SDL_INCLUDE_DIR ${THIRD_PARTY_DIR}/SDL/include)
    set(SDL_LIBRARY ${THIRD_PARTY_DIR}/SDL/lib/libSDL2.a)
    set(SDL_IMAGE_LIBRARY ${THIRD_PARTY_DIR}/SDL_image/lib/libSDL2_image.a)
    set(SDL_TTF_LIBRARY ${THIRD_PARTY_DIR}/SDL_ttf/lib/libSDL2_ttf.a)
    set(SDL_MIXER_LIBRARY ${THIRD_PARTY_DIR}/SDL_mixer/lib/libSDL2_mixer.a)
endif()

# Add engine headers and sources
file(GLOB_RECURSE HEADER_FILES "include/**/*.h")
file(GLOB_RECURSE SOURCE_FILES "src/**/*.cpp")

# Create Mira2D library
add_library(Mira2D STATIC ${HEADER_FILES} ${SOURCE_FILES} )

# Include GLAD (source files included)
add_subdirectory(${THIRD_PARTY_DIR}/glad)

target_include_directories(Mira2D SYSTEM PUBLIC 
    ${CMAKE_SOURCE_DIR}/Mira2D/include
    ${THIRD_PARTY_DIR}/glad/include
    ${THIRD_PARTY_DIR}/glm
    ${THIRD_PARTY_DIR}/SDL/include
    ${THIRD_PARTY_DIR}/SDL_image/include
    ${THIRD_PARTY_DIR}/SDL_mixer/include
    ${THIRD_PARTY_DIR}/SDL_ttf/include
)

target_link_libraries(Mira2D PRIVATE 
    glad 
    ${SDL_LIBRARY}
    ${SDL_MAIN_LIBRARY}  
    ${SDL_IMAGE_LIBRARY} 
    ${SDL_TTF_LIBRARY} 
    ${SDL_MIXER_LIBRARY}
)

# Ensure SDL dependencies are built before Mira2D
add_dependencies(Mira2D SDL SDL_image SDL_ttf SDL_mixer)