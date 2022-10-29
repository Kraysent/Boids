#pragma once
#include "Vector.h"

class Boid {
public: 
    Boid(Vector2 position, Vector2 velocity);
    Vector2 GetPosition() const;
    Vector2 GetVelocity() const;
    void Move(double dt);
    void Steer(double dalpha);

public:
    Vector2 Position;
    Vector2 Velocity;
};