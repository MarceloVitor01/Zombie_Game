#ifndef ANIMATION_H
#define ANIMATION_H

#include "SDL_include.h"

struct Animation
{
    int frameStart;
    int frameEnd;
    float frameTime;
    SDL_RendererFlip flip;

    Animation() : frameStart(0), frameEnd(0), frameTime(0), flip(SDL_FLIP_NONE) {}

    Animation(int start, int end, float time, SDL_RendererFlip flip = SDL_FLIP_NONE)
        : frameStart(start), frameEnd(end), frameTime(time), flip(flip) {}
};

#endif