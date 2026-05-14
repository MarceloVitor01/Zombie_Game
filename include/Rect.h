#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect
{
public:
    float x, y, w, h;

    Rect();
    Rect(float x, float y, float w, float h);

    bool Contains(float mouseX, float mouseY);
    Vec2 Center() const;
    void SetCenter(float centerX, float centerY);
    void SetCenter(const Vec2 &center);
    float Distance(const Rect &other) const;
};

#endif