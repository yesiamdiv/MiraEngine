# CMakeLists.txt for the local GLAD library
# =========================================
# This file builds the GLAD source files into a small static library
# that the main engine can link against.

# Create a static library target named 'glad'
add_library(glad STATIC src/glad.c)

# Specify the include directory for GLAD
target_include_directories(glad PUBLIC include)
