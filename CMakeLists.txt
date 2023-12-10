cmake_minimum_required(VERSION 3.25)
project(2D-Game)

set(CMAKE_CXX_STANDARD 14)

# Find SFML components
find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

include_directories(include)

# Configure resource files
configure_file(resources/background.png ${CMAKE_CURRENT_BINARY_DIR}/resources/background.png COPYONLY)
configure_file(resources/rocket.png ${CMAKE_CURRENT_BINARY_DIR}/resources/rocket.png COPYONLY)
configure_file(resources/RethinkSans-VariableFont_wght.ttf ${CMAKE_CURRENT_BINARY_DIR}/resources/RethinkSans-VariableFont_wght.ttf COPYONLY)
configure_file(resources/sphere.png ${CMAKE_CURRENT_BINARY_DIR}/resources/sphere.png COPYONLY)
configure_file(resources/planet1.png ${CMAKE_CURRENT_BINARY_DIR}/resources/planet1.png COPYONLY)
configure_file(resources/planet2.png ${CMAKE_CURRENT_BINARY_DIR}/resources/planet2.png COPYONLY)
configure_file(resources/planet3.png ${CMAKE_CURRENT_BINARY_DIR}/resources/planet3.png COPYONLY)
configure_file(resources/planet4.png ${CMAKE_CURRENT_BINARY_DIR}/resources/planet4.png COPYONLY)
configure_file(resources/planet5.png ${CMAKE_CURRENT_BINARY_DIR}/resources/planet5.png COPYONLY)
configure_file(resources/planet6.png ${CMAKE_CURRENT_BINARY_DIR}/resources/planet6.png COPYONLY)
configure_file(resources/planet7.png ${CMAKE_CURRENT_BINARY_DIR}/resources/planet7.png COPYONLY)
configure_file(resources/planet8.png ${CMAKE_CURRENT_BINARY_DIR}/resources/planet8.png COPYONLY)
configure_file(resources/caughtAlien.png ${CMAKE_CURRENT_BINARY_DIR}/resources/caughtAlien.png COPYONLY)


# Create the main executable
add_executable(2D-Game
    src/main.cpp
    src/game.cpp
    src/move.cpp
)

# Link the main executable with SFML libraries
target_link_libraries(2D-Game
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
