#include "Vec2.h"
#include <cmath>

Vec2::Vec2() : x(0), y(0) {}

Vec2::Vec2(float x, float y) : x(x), y(y) {}

Vec2 Vec2::operator+(const Vec2 &rhs) const
{
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2 &rhs) const
{
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(const float rhs) const
{
    return Vec2(x * rhs, y * rhs);
}

float Vec2::GetMagnitude() const
{
    return std::sqrt(x * x + y * y);
}

Vec2 Vec2::Normalize() const
{
    float m = GetMagnitude();
    if (m == 0)
        return Vec2(0, 0);
    return Vec2(x / m, y / m);
}

float Vec2::Distance(const Vec2 &other) const
{
    return (*this - other).GetMagnitude();
}

float Vec2::GetAngle() const
{
    return std::atan2(y, x);
}

float Vec2::GetAngle(const Vec2 &other) const
{
    return (other - *this).GetAngle();
}

Vec2 Vec2::GetRotated(float angle) const
{
    float cs = std::cos(angle);
    float sn = std::sin(angle);
    return Vec2(x * cs - y * sn, x * sn + y * cs);
}