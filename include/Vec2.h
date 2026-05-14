#ifndef VEC2_H
#define VEC2_H

class Vec2
{
public:
    float x, y;

    Vec2();
    Vec2(float x, float y);

    Vec2 operator+(const Vec2 &rhs) const;
    Vec2 operator-(const Vec2 &rhs) const;
    Vec2 operator*(const float rhs) const;

    float GetMagnitude() const;
    Vec2 Normalize() const;
    float Distance(const Vec2 &other) const;
    float GetAngle() const;
    float GetAngle(const Vec2 &other) const;
    Vec2 GetRotated(float angle) const;
};

#endif