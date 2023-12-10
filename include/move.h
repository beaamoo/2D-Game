#pragma once

struct Coordinate {
    float x, y;
};

Coordinate add(Coordinate a, Coordinate b);
Coordinate mul(float scalar, Coordinate a);
Coordinate move(Coordinate position, Coordinate velocity, float deltaTime);
