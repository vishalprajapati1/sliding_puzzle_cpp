cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
#file(GLOB Dir1_Sources RELATIVE "Library" "*.cpp")
#file(GLOB Dir2_Sources RELATIVE "Test" "*.cpp")

#add_executable(run_test ${Dir1_Sources} ${Dir2_Sources})

add_executable(
  run_test 
  Library/PuzzleState.cpp
  Library/PuzzleGenerator.cpp
  Library/PuzzleSolver.cpp
  Library/test.cpp
)

target_link_libraries(
  run_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(run_test)