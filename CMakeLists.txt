cmake_minimum_required(VERSION 3.20)
project(trafficLightController)

set(CMAKE_CXX_STANDARD 17)

# 1. Force a STATIC build. This bundles SFML directly into your .exe, completely eliminating DLLs!
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries" FORCE)

# 2. Tell CMake we don't need the extra SFML tutorials or docs to save download time
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC_API OFF CACHE BOOL "" FORCE)

# 3. Use FetchContent to download SFML directly from their official GitHub
include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.1.0
)
FetchContent_MakeAvailable(SFML)

# 4. Create your programme
add_executable(trafficLightController main.cpp
        Timer.h
        Signal.h
        VehicleLight.cpp
        VehicleLight.h
        PedestrianLight.cpp
        PedestrianLight.h
        Intersection.cpp
        Intersection.h
)

# 5. Link the modern SFML 3 targets.
# CMake will handle all the complex Windows dependencies automatically!
target_link_libraries(trafficLightController PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)