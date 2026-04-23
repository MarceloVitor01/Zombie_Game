#ifndef ANIMATION_H
#define ANIMATION_H

struct Animation
{
    int frameStart;
    int frameEnd;
    float frameTime;

    Animation() : frameStart(0), frameEnd(0), frameTime(0) {}
    Animation(int start, int end, float time) : frameStart(start), frameEnd(end), frameTime(time) {}
};

#endif