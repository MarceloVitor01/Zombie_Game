#ifndef VEC2_H
#define VEC2_H

class Vec2
{
public:
    float x;
    float y;

    Vec2();
    Vec2(float x, float y);

    Vec2 operator+(const Vec2 &rhs) const;
    Vec2 operator-(const Vec2 &rhs) const;
    Vec2 operator*(const float rhs) const;

    float Magnitude() const;
    Vec2 Normalize() const;
    float Distance(const Vec2 &dest) const;
    float Inclination() const;
    float InclinationD(const Vec2 &dest) const;
    Vec2 GetRotated(float angle) const;
};

#endif