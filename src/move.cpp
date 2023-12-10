#include "move.h"

// Add two coordinates
Coordinate add(Coordinate a, Coordinate b) {
    return {a.x + b.x, a.y + b.y};
}

// Multiply a coordinate by a scalar
Coordinate mul(float scalar, Coordinate a) {
    return {scalar * a.x, scalar * a.y};
}

// Move a coordinate by a velocity for a given time delta
Coordinate move(Coordinate position, Coordinate velocity, float deltaTime) {
    return add(position, mul(deltaTime, velocity));
}
