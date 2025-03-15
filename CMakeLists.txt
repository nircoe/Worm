cmake_minimum_required(VERSION 3.14)
project(Worm) # My Project Name

set_property(GLOBAL PROPERTY PROJECT_NAME "Worm")

# raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    if (NOT DEFINED RAYLIB_VERSION)
        set(RAYLIB_VERSION 5.5)
    endif()
    include(FetchContent)
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
    include(FetchContent)
    FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG ${RAYLIB_CPP_VERSION}
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

# cryptopp
set(CRYPTOPP_LIB_DIR "C:/Libraries/cryptopp-8.9.0/cryptopp/x64/Output/Release") # Path to cryptlib.lib
set(CRYPTOPP_INCLUDE_DIR "C:/Libraries/cryptopp-8.9.0/") # Path to cryptopp headers

# nlohmann/json
set(JSON_INCLUDE_DIR "C:/Libraries/json-cpp/")

# This is the main part:
# My source files here:
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# Add the include directory so that headers can be referenced directly
target_include_directories(${PROJECT_NAME} PRIVATE 
                            ${CMAKE_SOURCE_DIR}/include 
                            ${CRYPTOPP_INCLUDE_DIR} 
                            ${JSON_INCLUDE_DIR})

# Set output name based on build type
set_target_properties(${PROJECT_NAME} PROPERTIES 
    CXX_STANDARD 17
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib raylib_cpp ${CRYPTOPP_LIB_DIR}/cryptlib.lib)

# Treat warnings as errors
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W3 /WX)
endif()

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")

    # Required linker flags for using Raylib with Emscripten
    target_link_options(${PROJECT_NAME} PRIVATE -sEXPORTED_FUNCTIONS=['_main','_malloc'] -sEXPORTED_RUNTIME_METHODS=ccall -sUSE_GLFW=3)
endif()