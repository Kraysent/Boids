#pragma once

class Vector2 {
public:
    Vector2(double x, double y);
    void Rotate(double angle);
    double GetAngle() const;
    double Magnitude() const;
    void ScaleToMagnitude(double magnitude);
    Vector2 UnitVector();

    bool operator== (const Vector2& v) const;
    Vector2 operator+ (const Vector2& v) const;
    Vector2 operator- (const Vector2& v) const;
    Vector2 operator* (const double a) const;
    Vector2 operator/ (const double a) const;
    Vector2 operator+= (const Vector2& v);
    Vector2 operator-= (const Vector2& v);
    Vector2 operator*= (const double a);
    Vector2 operator/= (const double a);

    double X, Y;
};