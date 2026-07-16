cmake_minimum_required(VERSION 3.15)
project(RaylibVisualStudioProject CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_EXAMPLES OFF CACHE BOOL "Don't build raylib examples" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "Don't build raylib games" FORCE)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
)

FetchContent_MakeAvailable(raylib)

add_executable(Auto-Moeba Auto-Moeba.cpp "Particles/Particle.h" "Particles/Particle.cpp" "Utilities.h" "Utilities.cpp" "Particles.h" "Button.h" "Button.cpp" "Particles/TypeAttractions.h" "Particles/Predator.h" "Particles/Predator.cpp" "Particles/Prey.h" "Particles/Prey.cpp" "ParticleHandler.h" "ParticleHandler.cpp" "Particles/Food.h" "Particles/Food.cpp" "Particles/Waste.h" "Particles/Waste.cpp" "Particles/Scavenger.h" "Particles/Scavenger.cpp" "Particles/Nutrients.h" "Particles/Nutrients.cpp" "Particles/Membrane.h" "Particles/Membrane.cpp" "Particles/Nucleus.h" "Particles/Nucleus.cpp" "Particles/Connector.h" "Particles/Connector.cpp" "SaveSystem/Saver.h" "SaveSystem/FileUtils.h" "SaveSystem/Saver.cpp" "SaveSystem/FileUtils.cpp" "SaveSystem/PromptFile.cpp" "SaveSystem/GetExecutableDirectory.cpp")

target_link_libraries(Auto-Moeba PRIVATE raylib)

find_package(OpenMP REQUIRED)

if(OpenMP_CXX_FOUND)
	target_link_libraries(Auto-Moeba PRIVATE OpenMP::OpenMP_CXX)
	if(MSVC)
		target_compile_options(Auto-Moeba PRIVATE /openmp:llvm)
	endif()
endif()