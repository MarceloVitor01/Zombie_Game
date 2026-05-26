#ifndef COLLISION_H
#define COLLISION_H

#include "Rect.h"
#include "Vec2.h"
#include <algorithm>
#include <cmath>

class Collision
{
public:
    static inline bool IsColliding(Rect &a, Rect &b, float angleOfA, float angleOfB)
    {
        Vec2 A[] = {Vec2(a.x, a.y + a.h), Vec2(a.x + a.w, a.y + a.h), Vec2(a.x + a.w, a.y), Vec2(a.x, a.y)};
        Vec2 B[] = {Vec2(b.x, b.y + b.h), Vec2(b.x + b.w, b.y + b.h), Vec2(b.x + b.w, b.y), Vec2(b.x, b.y)};

        for (auto &v : A)
        {
            v = (v - a.Center()).GetRotated(angleOfA) + a.Center();
        }
        for (auto &v : B)
        {
            v = (v - b.Center()).GetRotated(angleOfB) + b.Center();
        }

        Vec2 axes[] = {(A[0] - A[1]).Normalize(), (A[1] - A[2]).Normalize(), (B[0] - B[1]).Normalize(), (B[1] - B[2]).Normalize()};

        for (auto &axis : axes)
        {
            float P[4];
            for (int i = 0; i < 4; ++i)
                P[i] = A[i].x * axis.x + A[i].y * axis.y;
            float minA = *std::min_element(P, P + 4), maxA = *std::max_element(P, P + 4);
            for (int i = 0; i < 4; ++i)
                P[i] = B[i].x * axis.x + B[i].y * axis.y;
            float minB = *std::min_element(P, P + 4), maxB = *std::max_element(P, P + 4);
            if (maxA < minB || minA > maxB)
                return false;
        }
        return true;
    }
};

#endif