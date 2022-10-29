#include "Boid.h"
#include "Vector.h"

Boid::Boid(Vector2 position, Vector2 velocity) : 
    Position(position), Velocity(velocity) { }

Vector2 Boid::GetPosition() const {
    return Position;
}

Vector2 Boid::GetVelocity() const {
    return Velocity;
}

void Boid::Move(double dt) {
    Position += Velocity * dt;
}

void Boid::Steer(double dalpha) {
    Velocity.Rotate(dalpha);
}