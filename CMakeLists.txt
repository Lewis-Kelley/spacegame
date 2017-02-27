cmake_minimum_required(VERSION 2.6)
project(spacegame)
include(FindPkgConfig)

# enable_testing()

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS}
  ${SDL2IMAGE_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "-g -O0 -Wall")

file(GLOB sources "src/*.cpp")

add_executable(spacegame ${sources})
target_link_libraries(spacegame ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
