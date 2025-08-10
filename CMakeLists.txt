cmake_minimum_required(VERSION 3.10)
project(New_APPLICATION C)

set(CMAKE_C_STANDARD 99)

# --- Raylib Configuration ---
# Set this to the root folder of your raylib installation.
# For example: "C:/raylib/raylib-4.5.0"
set(RAYLIB_PATH "RAYLIB/raylib-5.5_win64_mingw-w64")
# --- End of Raylib Configuration ---

# Add the raylib header files to the include path
include_directories(${RAYLIB_PATH}/include)

# Add the raylib library files to the link path
link_directories(${RAYLIB_PATH}/lib)

# Add your executable
add_executable(New_APPLICATION raylibhelloworld.c)

# Link the raylib library to your executable
# This is the most important step!
target_link_libraries(New_APPLICATION PRIVATE raylib)

# On Windows, link against system libraries that raylib depends on
if (WIN32)
    target_link_libraries(New_APPLICATION PRIVATE winmm gdi32)
endif()