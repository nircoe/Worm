cmake_minimum_required(VERSION 3.14)
project(Worm) # My Project Name

set_property(GLOBAL PROPERTY PROJECT_NAME "Worm")

include(FetchContent)
# raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    if (NOT DEFINED RAYLIB_VERSION)
        set(RAYLIB_VERSION 5.5)
    endif()
    message(STATUS "[Worm]: fetching raylib from source...")
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG ${RAYLIB_VERSION}
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
    message(STATUS "[Worm]: fetching raylib-cpp from source...")
    FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG ${RAYLIB_CPP_VERSION}
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(external/datacoe)

# Disable PulseAudio backend for CI environments (PipeWire and ALSA are sufficient)
set(SOUNDCOE_ENABLE_PULSEAUDIO OFF CACHE BOOL "Disable PulseAudio backend")

message(STATUS "[Worm]: fetching soundcoe from source...")
FetchContent_Declare(
    soundcoe
    GIT_REPOSITORY https://github.com/nircoe/soundcoe.git
    GIT_TAG main
)
FetchContent_MakeAvailable(soundcoe)

# This is the main part:
# My source files here:
add_executable(${PROJECT_NAME}
    src/transform2d.cpp
    src/button.cpp
    src/textbox.cpp
    src/text.cpp
    src/moveable.cpp
    src/game_object.cpp
    src/scene.cpp
    src/new_game_scene.cpp
    src/home_scene.cpp
    src/game_scene.cpp
    src/game_manager.cpp
    src/food.cpp
    src/player.cpp
    src/home_scene_player.cpp
    src/main.cpp
)

# Add the include directory so that headers can be referenced directly
target_include_directories(${PROJECT_NAME} PRIVATE 
                            ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set output name based on build type
set_target_properties(${PROJECT_NAME} PROPERTIES 
    CXX_STANDARD 17
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib raylib_cpp datacoe soundcoe)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
    COMMENT "Copying assets to build directory")

# Treat warnings as errors
# if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#     target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
# elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#     target_compile_options(${PROJECT_NAME} PRIVATE /W3 /WX)
# endif()

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")

    # Required linker flags for using Raylib with Emscripten
    target_link_options(${PROJECT_NAME} PRIVATE -sEXPORTED_FUNCTIONS=['_main','_malloc'] -sEXPORTED_RUNTIME_METHODS=ccall -sUSE_GLFW=3)
endif()