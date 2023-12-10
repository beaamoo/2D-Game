cmake_minimum_required(VERSION 3.25)
project(2D-Game)

set(CMAKE_CXX_STANDARD 14)

# Include directories for SFML and Google Test
include_directories(
    include
    /opt/homebrew/Cellar/sfml/2.6.1/include
    /opt/homebrew/Cellar/googletest/1.14.0/include/gmock
    /opt/homebrew/Cellar/googletest/1.14.0/include/googlemock
    /opt/homebrew/Cellar/googletest/1.14.0/include/googletest
    /opt/homebrew/Cellar/googletest/1.14.0/include/gtest
)

# Configure resource files
configure_file(resources/background.png ${CMAKE_CURRENT_BINARY_DIR}/resources/background.png COPYONLY)
configure_file(resources/pacman.png ${CMAKE_CURRENT_BINARY_DIR}/resources/pacman.png COPYONLY)
configure_file(resources/RethinkSans-VariableFont_wght.ttf ${CMAKE_CURRENT_BINARY_DIR}/resources/RethinkSans-VariableFont_wght.ttf COPYONLY)

# Create the main executable
add_executable(2D_game_assignment
    src/main.cpp
    src/game.cpp
    src/move.cpp
)

# Link the main executable with SFML libraries
target_link_libraries(2D_game_assignment
    sfml-graphics
    sfml-window
    sfml-system
)

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