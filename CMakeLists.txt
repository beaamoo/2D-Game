cmake_minimum_required(VERSION 3.25)
project(2D_game_assignment)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(/usr/local/Cellar/sfml/2.6.1/include)
link_directories(/usr/local/Cellar/sfml/2.6.1/lib)

configure_file(resources/background.png ${CMAKE_CURRENT_BINARY_DIR}/resources/background.png COPYONLY)
configure_file(resources/pacman.png ${CMAKE_CURRENT_BINARY_DIR}/resources/pacman.png COPYONLY)

# Main application executable
add_executable(2D_game_assignment
        src/main.cpp
        src/game.cpp
        src/move.cpp
)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

# Fetch Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Test executable
add_executable(coordinate_test
        src/move.cpp
        test/CoordinateTest.cpp
)

target_link_libraries(coordinate_test gtest_main)
include(GoogleTest)
gtest_discover_tests(coordinate_test)