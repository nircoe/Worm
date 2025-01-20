cmake_minimum_required(VERSION 3.14)
project(Worm) # My Project Name

set_property(GLOBAL PROPERTY PROJECT_NAME "Worm")

# Set compiler flags - treat warnings as errors
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /WX")


# raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
        GIT_SHALLOW 1
    )
    FetchContent_MakeAvailable(raylib)
endif()

# raylib-cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    if (NOT DEFINED RAYLIB_CPP_VERSION)
        set(RAYLIB_CPP_VERSION v5.5.0)
    endif()
    include(FetchContent)
    FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG ${RAYLIB_CPP_VERSION}
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

# This is the main part:
# My source files here:
set(SOURCES 
    src/transform2d.cpp
    src/game_object.cpp
    src/moveable.cpp
    src/player.cpp
    src/home_scene_player.cpp
    src/food.cpp
    src/scene.cpp
    src/game_manager.cpp
    src/home_scene.cpp
    src/game_scene.cpp
    src/main.cpp
    # any other source file in the future
)
add_executable(${PROJECT_NAME} ${SOURCES})

# Add the include directory so that headers can be referenced directly
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Set output name based on build type
set_target_properties(${PROJECT_NAME} PROPERTIES 
    CXX_STANDARD 17
)

target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")

    # Required linker flags for using Raylib with Emscripten
    target_link_options(${PROJECT_NAME} PRIVATE -sEXPORTED_FUNCTIONS=['_main','_malloc'] -sEXPORTED_RUNTIME_METHODS=ccall -sUSE_GLFW=3)
endif()

# That's it! You should have an example executable that you can run. Have fun!