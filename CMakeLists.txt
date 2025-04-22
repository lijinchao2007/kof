cmake_minimum_required(VERSION 3.27)
set(PROJECT kof)
project(${PROJECT})

# Add global definitions
file(GLOB_RECURSE SOURCE_FILES
"src/*.cpp"
"src/*.c")

file(GLOB_RECURSE HEADER_FILES "src/*.h"
"src/*.l"
)
add_executable(${PROJECT} ${SOURCE_FILES} ${HEADER_FILES})

message("CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
message("CMAKE_CXX_COMPILER_VERSION: ${CMAKE_CXX_COMPILER_VERSION}")

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions("-g -O0 -Wall -Wextra -Wpedantic")
    add_definitions("-fsanitize=address")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_GFX REQUIRED SDL2_gfx)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(GLESV2 REQUIRED glesv2)

message(STATUS "SDL2_INCLUDE_DIRS: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2_LIBRARY_DIRS: ${SDL2_LIBRARY_DIRS}")
message(STATUS "GLEW_INCLUDE_DIRS: ${GLEW_INCLUDE_DIRS}")

target_compile_options(${PROJECT} PRIVATE -Wall -Wextra -Wpedantic)
include_directories(
    src
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_GFX_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_MIXER_LIBRARY_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLESV2_INCLUDE_DIRS}
)

link_directories(
    ${SDL2_LIBRARY_DIRS}
    ${SDL2_IMAGE_LIBRARY_DIRS}
    ${SDL2_GFX_LIBRARY_DIRS}
    ${SDL2_TTF_LIBRARY_DIRS}
    ${SDL2_MIXER_LIBRARY_DIRS}
    ${GLEW_LIBRARY_DIRS}
    ${GLESV2_LIBRARY_DIRS}
)
message(STATUS "GLEW_LIBRARY_DIRS: ${GLEW_LIBRARY_DIRS}")
target_link_libraries(${PROJECT}
    -L${SDL2_LIBRARY_DIRS}
    -L${SDL2_IMAGE_LIBRARY_DIRS}
    -L${SDL2_GFX_LIBRARY_DIRS}
    -lSDL2
    -lSDL2_image
    -lSDL2_gfx
    -lSDL2_mixer
    -lSDL2_ttf
    -lGLEW
    -lGLESv2
    -lGL
)