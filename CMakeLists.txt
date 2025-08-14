cmake_minimum_required(VERSION 3.1.0...4.0.0)

project(RTWeekend LANGUAGES CXX)

include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

# Fetches the raylib library and constructs the path
FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS true
)

FetchContent_MakeAvailable(raylib)

set( CMAKE_CXX_STANDARD 17)
set( CMAKE_CXX_STANDARD_REQUIRED ON)

set( SOURCE_ONE_WEEKEND 
    src/main.cpp
    src/ray.h
    src/color.h
    src/vec.h
    src/hittable.h
    src/sphere.h
    src/hittable_list.h
    src/rtweekend.h
    src/interval.h
    src/camera.h
    src/material.h
    )

include_directories(src)

message (STATUS "Compiler ID: " ${CMAKE_CXX_COMPILER_ID})
message (STATUS "Release flags: " ${CMAKE_CXX_FLAGS_RELEASE})
message (STATUS "Debug flags: " ${CMAKE_CXX_FLAGS_DEBUG})

add_compile_options(-Wnon-virtual-dtor) # Class has virtual functions, but its destructor is not virtual
add_compile_options(-Wreorder) # Data member will be initialized after [other] data member
add_compile_options(-Wsometimes-uninitialized) # Variable improperly initialized
add_compile_options(-Wunused-variable) # Variable is defined but unused

add_executable(inOneWeekend      ${EXTERNAL} ${SOURCE_ONE_WEEKEND})
target_link_libraries(inOneWeekend PRIVATE raylib)