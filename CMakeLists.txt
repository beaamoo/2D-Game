cmake_minimum_required(VERSION 3.25)
project(2D_game_assignment)

# Set the C++ standard to C++14
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

# Test suite sources
set(TEST_SOURCES
    src/move.cpp
    test/CoordinateTest.cpp
)

# Add the Google Test framework
find_package(GTest REQUIRED)

# Include Google Test headers
include_directories(${GTEST_INCLUDE_DIRS})

# Create the test executable
add_executable(CoordinateTest ${TEST_SOURCES})

# Link the test executable with Google Test libraries and pthread
target_link_libraries(CoordinateTest
    ${GTEST_BOTH_LIBRARIES}
    pthread
)

# Link the test executable with Google Test and Google Test Main
target_link_libraries(CoordinateTest
    GTest::GTest
    GTest::Main
)

# Specify the executable output directory for tests
set_target_properties(CoordinateTest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/test
)

# Add a test target for running tests using ctest
add_test(NAME CoordinateTest COMMAND CoordinateTest)
