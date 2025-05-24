# Glad project configuration
project(glad)

# Add glad source files
add_library(glad STATIC src/glad.c)

# Specify include directories
target_include_directories(glad PUBLIC include)
