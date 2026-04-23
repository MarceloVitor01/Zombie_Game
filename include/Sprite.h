#ifndef SPRITE_H
#define SPRITE_H

#include "SDL_include.h"
#include <string>

class Sprite
{
public:
    Sprite();
    Sprite(std::string file, int frameCountW = 1, int frameCountH = 1);
    ~Sprite();

    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void SetFrame(int frame);
    void SetFrameCount(int frameCountW, int frameCountH);

    void Render(int x, int y);

    int GetWidth();
    int GetHeight();
    bool IsOpen();

private:
    SDL_Texture *texture;
    int width;
    int height;
    SDL_Rect clipRect;
    int frameCountW;
    int frameCountH;
    int currentFrame;
};

#endif