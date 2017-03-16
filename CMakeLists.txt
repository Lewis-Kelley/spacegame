cmake_minimum_required(VERSION 2.8.2)

set(CMAKE_CXX_COMPILER "g++-4.9.3")
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -std=c++11")

project(spacegame)
include(FindPkgConfig)

enable_testing()

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS}
  ${SDL2IMAGE_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB sources "src/*/*.cpp")
file(GLOB_RECURSE headers "src/*.hpp")

add_executable(spacegame ${sources} "src/main.cpp")
target_link_libraries(spacegame ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

add_executable(SpriteTest "test/SpriteTest.cpp" ${sources})
target_link_libraries(SpriteTest gtest_main gmock_main "-pthread")
target_link_libraries(SpriteTest ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
add_test(NAME sprite_test COMMAND SpriteTest)
