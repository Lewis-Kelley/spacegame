cmake_minimum_required(VERSION 2.8.2)

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
  ${CMAKE_BINARY_DIR}/googletest-build)


# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

project(spacegame)
include(FindPkgConfig)

enable_testing()

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS}
  ${SDL2IMAGE_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -std=c++11")

file(GLOB sources "src/*/*.cpp")
file(GLOB_RECURSE headers "src/*.hpp")

add_executable(spacegame ${sources} "src/main.cpp")
target_link_libraries(spacegame ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

add_executable(SpriteTest "test/SpriteTest.cpp" ${sources})
target_link_libraries(SpriteTest gtest_main gmock_main)
target_link_libraries(SpriteTest ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
add_test(NAME sprite_test COMMAND SpriteTest)
