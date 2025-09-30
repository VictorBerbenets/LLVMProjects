cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_COLOR_DIAGNOSTICS ON)

project(SDL)

find_package(SDL2 REQUIRED)

add_executable(sdl main.c app.c simulator.c)
target_include_directories(sdl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS})
target_link_libraries(sdl ${SDL2_LIBRARIES})
