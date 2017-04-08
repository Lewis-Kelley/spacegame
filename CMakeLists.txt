cmake_minimum_required(VERSION 2.8.2)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -std=c++11")

project(spacegame)
include(FindPkgConfig)

enable_testing()

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS}
  ${SDL2IMAGE_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR})

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
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

file(GLOB sources "src/*/*.cpp")
file(GLOB_RECURSE headers "src/*.hpp")

add_executable(spacegame ${sources} "src/main.cpp")
target_link_libraries(spacegame ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

add_executable(TestSprite "test/drawables/TestSprite.cpp"
  "src/drawables/Sprite.cpp" "src/drawables/Renderer.cpp"
  "src/drawables/Drawable.cpp" "src/drawables/Texture.cpp")
target_link_libraries(TestSprite gtest gtest_main gmock gmock_main "-pthread")
target_link_libraries(TestSprite ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
add_test(NAME sprite_test COMMAND TestSprite)

add_executable(TestEventHandler "test/events/TestEventHandler.cpp"
  "src/events/EventHandler.cpp")
target_link_libraries(TestEventHandler gtest gtest_main gmock gmock_main "-pthread")
add_test(NAME test_event_handler COMMAND TestEventHandler)

add_executable(TestQuitListener "test/listeners/TestQuitListener.cpp"
  "src/listeners/QuitListener.cpp" "src/events/EventHandler.cpp"
  "src/util/GameState.cpp" "src/util/Window.cpp" "src/drawables/Renderer.cpp"
  "src/drawables/Texture.cpp")
target_link_libraries(TestQuitListener ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
target_link_libraries(TestQuitListener gtest gtest_main gmock gmock_main "-pthread")
add_test(NAME test_quit_listener COMMAND TestQuitListener)

add_executable(TestDirection "test/util/TestDirection.cpp"
  "src/util/Direction.cpp")
target_link_libraries(TestDirection gtest gtest_main gmock gmock_main "-pthread")
add_test(NAME test_direction COMMAND TestDirection)
