# Mira Engine - cmake/dependencies.cmake
# ======================================
# This file uses a modern, data-driven approach to manage dependencies.

include(FetchContent)
include(CMakeParseArguments)

# --------------------------------------------------------------------
# PART 1: The Function to Register a Dependency's "Recipe"
# --------------------------------------------------------------------
# This function stores all information about a dependency in global properties.
# It does NOT fetch or link anything itself.
function(mira_register_dependency NAME)
    # Define arguments: TARGETS and EXPORTED_TARGETS are lists.
    set(options "")
    set(oneValueArgs GIT_REPOSITORY GIT_TAG)
    set(multiValueArgs TARGETS EXPORTED_TARGETS)
    cmake_parse_arguments(DEP "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Store all the parsed data in global properties, prefixed with the name.
    set_property(GLOBAL PROPERTY _mira_dep_${NAME}_repo    "${DEP_GIT_REPOSITORY}")
    set_property(GLOBAL PROPERTY _mira_dep_${NAME}_tag     "${DEP_GIT_TAG}")
    set_property(GLOBAL PROPERTY _mira_dep_${NAME}_targets "${DEP_TARGETS}")
    set_property(GLOBAL PROPERTY _mira_dep_${NAME}_exports "${DEP_EXPORTED_TARGETS}")

    # Add this dependency's name to a master list of all dependencies.
    set_property(GLOBAL APPEND PROPERTY _mira_registered_deps ${NAME})
endfunction()

# --------------------------------------------------------------------
# PART 2: The Action Functions (Behavior)
# --------------------------------------------------------------------
# This function iterates over the master list and fetches everything.
function(mira_fetch_all_dependencies)
    message(STATUS "Fetching all registered dependencies...")
    get_property(dep_names GLOBAL PROPERTY _mira_registered_deps)

    foreach(dep_name ${dep_names})
        get_property(repo GLOBAL PROPERTY _mira_dep_${dep_name}_repo)
        get_property(tag  GLOBAL PROPERTY _mira_dep_${dep_name}_tag)

        FetchContent_Declare(${dep_name} GIT_REPOSITORY ${repo} GIT_TAG ${tag})
        FetchContent_MakeAvailable(${dep_name})
    endforeach()
endfunction()

# This function iterates over the master list and links everything.
function(mira_link_all_dependencies)
    message(STATUS "Linking all registered dependencies...")
    get_property(dep_names GLOBAL PROPERTY _mira_registered_deps)

    foreach(dep_name ${dep_names})
        get_property(link_targets GLOBAL PROPERTY _mira_dep_${dep_name}_targets)
        get_property(exports      GLOBAL PROPERTY _mira_dep_${dep_name}_exports)

        if(link_targets AND exports)
             message(STATUS "Linking ${exports} to ${link_targets}")
             target_link_libraries(${link_targets} PUBLIC ${exports})
        endif()
    endforeach()
endfunction()

# --------------------------------------------------------------------
# PART 3: The Dependency List (Data)
# --------------------------------------------------------------------
# THIS IS NOW THE ONLY SECTION YOU NEED TO EDIT TO ADD/REMOVE LIBRARIES.

mira_register_dependency(SDL
    GIT_REPOSITORY   https://github.com/libsdl-org/SDL.git
    GIT_TAG          release-2.30.0
    EXPORTED_TARGETS SDL2::SDL2 SDL2::SDL2main       
    TARGETS          Mira2D              
)

mira_register_dependency(SDL_image
    GIT_REPOSITORY   https://github.com/libsdl-org/SDL_image.git
    GIT_TAG          release-2.8.0
    EXPORTED_TARGETS SDL2_image::SDL2_image
    TARGETS          Mira2D
)

mira_register_dependency(SDL_mixer
    GIT_REPOSITORY   https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG          release-2.8.0
    EXPORTED_TARGETS SDL2_mixer::SDL2_mixer
    TARGETS          Mira2D
)

mira_register_dependency(SDL_ttf
    GIT_REPOSITORY   https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG          release-2.22.0
    EXPORTED_TARGETS SDL2_ttf::SDL2_ttf
    TARGETS          Mira2D
)

mira_register_dependency(glm
    GIT_REPOSITORY   https://github.com/g-truc/glm.git
    GIT_TAG          0.9.9.8
    EXPORTED_TARGETS glm::glm
    TARGETS          Mira2D
)



