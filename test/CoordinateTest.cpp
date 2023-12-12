// CoordinateTest.cpp
#include <gtest/gtest.h>
#include "move.h"

// Test for adding two coordinates
TEST(CoordinateTest, Add) {
    Coordinate a = {1.0, 2.0};
    Coordinate b = {3.0, 4.0};
    Coordinate result = add(a, b);
    EXPECT_FLOAT_EQ(result.x, 4.0);
    EXPECT_FLOAT_EQ(result.y, 6.0);
}

// Test for multiplying a coordinate by a scalar
TEST(CoordinateTest, Mul) {
    Coordinate a = {1.0, 2.0};
    float scalar = 2.0;
    Coordinate result = mul(scalar, a);
    EXPECT_FLOAT_EQ(result.x, 2.0);
    EXPECT_FLOAT_EQ(result.y, 4.0);
}

// Test for moving a coordinate by a velocity for a given time delta
TEST(CoordinateTest, Move) {
    Coordinate position = {1.0, 2.0};
    Coordinate velocity = {2.0, 3.0};
    float deltaTime = 0.5;
    Coordinate result = move(position, velocity, deltaTime);
    EXPECT_FLOAT_EQ(result.x, 2.0);
    EXPECT_FLOAT_EQ(result.y, 3.5);
}

// Additional tests for edge cases and more scenarios

// Test adding with zero
TEST(CoordinateTest, AddWithZero) {
    Coordinate a = {5.0, 10.0};
    Coordinate zero = {0.0, 0.0};
    Coordinate result = add(a, zero);
    EXPECT_FLOAT_EQ(result.x, 5.0);
    EXPECT_FLOAT_EQ(result.y, 10.0);
}

// Test multiplying with zero
TEST(CoordinateTest, MulWithZero) {
    Coordinate a = {5.0, 10.0};
    float scalar = 0.0;
    Coordinate result = mul(scalar, a);
    EXPECT_FLOAT_EQ(result.x, 0.0);
    EXPECT_FLOAT_EQ(result.y, 0.0);
}

// Test moving with zero velocity
TEST(CoordinateTest, MoveWithZeroVelocity) {
    Coordinate position = {1.0, 2.0};
    Coordinate velocity = {0.0, 0.0};
    float deltaTime = 1.0;
    Coordinate result = move(position, velocity, deltaTime);
    EXPECT_FLOAT_EQ(result.x, 1.0);
    EXPECT_FLOAT_EQ(result.y, 2.0);
}

// Test moving with negative velocity
TEST(CoordinateTest, MoveWithNegativeVelocity) {
    Coordinate position = {10.0, 20.0};
    Coordinate velocity = {-2.0, -3.0};
    float deltaTime = 1.0;
    Coordinate result = move(position, velocity, deltaTime);
    EXPECT_FLOAT_EQ(result.x, 8.0);
    EXPECT_FLOAT_EQ(result.y, 17.0);
}

// Test adding inverse coordinates (should result in zero)
TEST(CoordinateTest, AddInverse) {
    Coordinate a = {5.0, 10.0};
    Coordinate inverse_a = {-5.0, -10.0};
    Coordinate result = add(a, inverse_a);
    EXPECT_FLOAT_EQ(result.x, 0.0);
    EXPECT_FLOAT_EQ(result.y, 0.0);
}
