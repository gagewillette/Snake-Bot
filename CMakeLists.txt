cmake_minimum_required(VERSION 4.3)
project(snake_bot)

# Include FetchContent module
include(FetchContent)

# SDL2's own CMakeLists.txt declares a cmake_minimum_required below 3.5,
# which CMake 4.x refuses to configure. Allow it for fetched dependencies.
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

# Declare SDL dependency
FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG        release-2.26.3 # Or use a specific tag like release-2.30.0 for SDL2
)

# Make the populated content available
FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
        SDL2_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG release-2.6.3
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)

# START ADDITION
set(SDL2IMAGE_INSTALL OFF)
set(BUILD_SHARED_LIBS FALSE)
# END ADDITION

FetchContent_MakeAvailable(SDL2_image)

# Add your executable
add_executable(snake_bot src/main.cpp
        src/Game.cpp
        src/Game.h
        src/Cell.cpp
        src/Cell.h
        src/Snake.cpp
        src/Snake.h
)

# Link your executable against SDL
# For SDL3 use: SDL3::SDL3-shared (or SDL3::SDL3-static)
# For SDL2 use: SDL2::SDL2
target_link_libraries(snake_bot PRIVATE SDL2::SDL2)

