#include "Rect.h"

Rect::Rect() : x(0), y(0), w(0), h(0) {}

Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

bool Rect::Contains(float mouseX, float mouseY)
{
    return (mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h);
}

Vec2 Rect::Center() const
{
    return Vec2(x + w / 2.0f, y + h / 2.0f);
}

void Rect::SetCenter(float centerX, float centerY)
{
    x = centerX - w / 2.0f;
    y = centerY - h / 2.0f;
}

void Rect::SetCenter(const Vec2 &center)
{
    x = center.x - w / 2.0f;
    y = center.y - h / 2.0f;
}

float Rect::Distance(const Rect &other) const
{
    return Center().Distance(other.Center());
}