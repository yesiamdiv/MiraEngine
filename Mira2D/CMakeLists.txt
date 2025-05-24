cmake_minimum_required(VERSION 3.15)
project(Mira2D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set third-party directory
set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/Mira2D/third_party)
set(SOURCES_DIR ${THIRD_PARTY_DIR}/sources)
set(BUILD_DIR ${THIRD_PARTY_DIR}/build)

include(ExternalProject)

# Helper to build SDL libs from local source archive
function(build_sdl_lib name archive_name extra_args)
    set(ARCHIVE_PATH ${SOURCES_DIR}/${archive_name})
    set(INSTALL_DIR ${BUILD_DIR}/${name})

    if(NOT name STREQUAL "SDL")
        set(SDL2_DIR_ARG -DSDL2_DIR=${BUILD_DIR}/SDL)
        set(PREFIX_PATH_ARG -DCMAKE_PREFIX_PATH=${BUILD_DIR}/SDL)
    else()
        set(SDL2_DIR_ARG "")
        set(PREFIX_PATH_ARG "")
    endif()

    ExternalProject_Add(
        ${name}
        URL ${ARCHIVE_PATH}
        DOWNLOAD_EXTRACT_TIMESTAMP true
        PREFIX ${BUILD_DIR}/${name}_prefix
        CMAKE_ARGS
            -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
            -DBUILD_SHARED_LIBS=OFF
            ${SDL2_DIR_ARG}
            ${PREFIX_PATH_ARG}
            ${extra_args}
    )
endfunction()

# Download and build SDL libraries (Windows / Linux)
# if(WIN32)
#     build_sdl_lib(SDL SDL-release-2.30.10.zip "")
#     build_sdl_lib(SDL_image SDL_image-release-2.8.4.zip "-DSDL2IMAGE_VENDORED=ON -DSDL2IMAGE_DOWNLOAD_DEPENDENCIES=ON")
#     build_sdl_lib(SDL_ttf SDL_ttf-release-2.24.0.zip "-DSDL2TTF_VENDORED=ON -DSDL2TTF_DOWNLOAD_DEPENDENCIES=ON")
#     build_sdl_lib(SDL_mixer SDL_mixer-release-2.8.1.zip "")
# else()
#     build_sdl_lib(SDL SDL-release-2.30.10.tar.gz "")
#     build_sdl_lib(SDL_image SDL_image-release-2.8.4.tar.gz "-DSDL2IMAGE_VENDORED=ON -DSDL2IMAGE_DOWNLOAD_DEPENDENCIES=ON")
#     build_sdl_lib(SDL_ttf SDL_ttf-release-2.24.0.tar.gz "-DSDL2TTF_VENDORED=ON -DSDL2TTF_DOWNLOAD_DEPENDENCIES=ON")
#     build_sdl_lib(SDL_mixer SDL_mixer-release-2.8.1.tar.gz "")
# endif()

if(WIN32)
    build_sdl_lib(SDL SDL2-2.30.10.zip "")
    build_sdl_lib(SDL_image SDL2_image-2.8.4.zip "-DSDL2IMAGE_VENDORED=ON -DSDL2IMAGE_DOWNLOAD_DEPENDENCIES=ON")
    build_sdl_lib(SDL_ttf SDL2_ttf-2.24.0.zip "-DSDL2TTF_VENDORED=ON -DSDL2TTF_DOWNLOAD_DEPENDENCIES=ON")
    build_sdl_lib(SDL_mixer SDL2_mixer-2.8.1.zip "")
else()
    build_sdl_lib(SDL SDL2-2.30.10.tar.gz "")
    build_sdl_lib(SDL_image SDL2_image-2.8.4.tar.gz "-DSDL2IMAGE_VENDORED=ON -DSDL2IMAGE_DOWNLOAD_DEPENDENCIES=ON")
    build_sdl_lib(SDL_ttf SDL2_ttf-2.24.0.tar.gz "-DSDL2TTF_VENDORED=ON -DSDL2TTF_DOWNLOAD_DEPENDENCIES=ON")
    build_sdl_lib(SDL_mixer SDL2_mixer-2.8.1.tar.gz "")
endif()

# Set include/library paths to the build output
set(SDL_INCLUDE_DIR ${BUILD_DIR}/SDL/include/SDL2)
set(SDL_LIBRARY ${BUILD_DIR}/SDL/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2-staticd${CMAKE_STATIC_LIBRARY_SUFFIX})
set(SDL_MAIN_LIBRARY ${BUILD_DIR}/SDL/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2maind${CMAKE_STATIC_LIBRARY_SUFFIX})
set(SDL_IMAGE_LIBRARY ${BUILD_DIR}/SDL_image/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_image-staticd${CMAKE_STATIC_LIBRARY_SUFFIX})
set(SDL_TTF_LIBRARY ${BUILD_DIR}/SDL_ttf/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_ttfd${CMAKE_STATIC_LIBRARY_SUFFIX})
set(SDL_MIXER_LIBRARY ${BUILD_DIR}/SDL_mixer/lib/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2_mixer-staticd${CMAKE_STATIC_LIBRARY_SUFFIX})

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
    ${SDL_INCLUDE_DIR}
    ${BUILD_DIR}/SDL_image/include/SDL2
    ${BUILD_DIR}/SDL_mixer/include/SDL2
    ${BUILD_DIR}/SDL_ttf/include/SDL2
)

target_link_libraries(Mira2D PRIVATE 
    glad 
    ${SDL_LIBRARY}
    ${SDL_MAIN_LIBRARY}
    ${SDL_IMAGE_LIBRARY}
    ${SDL_TTF_LIBRARY}
    ${SDL_MIXER_LIBRARY}
    winmm
    imm32
    version
    setupapi
    cfgmgr32
)

# Ensure SDL dependencies are built before Mira2D
add_dependencies(Mira2D SDL SDL_image SDL_ttf SDL_mixer)

set(SDL_TTF_EXTRA_ARGS -DSDL2TTF_VENDORED=ON -DSDL2TTF_DOWNLOAD_DEPENDENCIES=ON)