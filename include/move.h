/*
 * File: move.h
 * Author: Beatrice Mossberg
 * Date: November 23, 2023
 * Description: Move header.
 */

struct Coordinate {
    float x;
    float y;
};

Coordinate add(Coordinate x, Coordinate y);

Coordinate mul(float s, Coordinate a);

Coordinate move(Coordinate position, Coordinate velocity, float delta);