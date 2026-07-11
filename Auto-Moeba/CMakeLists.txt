cmake_minimum_required(VERSION 3.15)
project(RaylibVisualStudioProject CXX)

# Force C++17 or higher for compatibility
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure raylib options BEFORE fetching it
set(BUILD_EXAMPLES OFF CACHE BOOL "Don't build raylib examples" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "Don't build raylib games" FORCE)

# Include the FetchContent module
include(FetchContent)

# Declare raylib dependency (uses the latest stable branch or tag)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master" # You can replace "master" with a specific version like "5.0"
)

# Download and make raylib targets available to CMake
FetchContent_MakeAvailable(raylib)

# Define your game executable
add_executable(Auto-Moeba Auto-Moeba.cpp "Particles/Particle.h" "Particles/Particle.cpp" "Utilities.h" "Utilities.cpp" "Particles.h" "Button.h" "Button.cpp" "Particles/TypeAttractions.h" "Particles/Predator.h" "Particles/Predator.cpp" "Particles/Prey.h" "Particles/Prey.cpp" "ParticleHandler.h" "ParticleHandler.cpp" "Particles/Food.h" "Particles/Food.cpp")

# Link your executable to raylib
target_link_libraries(Auto-Moeba PRIVATE raylib)