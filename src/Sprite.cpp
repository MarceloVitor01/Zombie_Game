#include "Sprite.h"
#include "Game.h"
#include "Resources.h"

Sprite::Sprite()
{
    texture = nullptr;
    frameCountW = 1;
    frameCountH = 1;
    currentFrame = 0;
}

Sprite::Sprite(std::string file, int frameCountW, int frameCountH)
{
    texture = nullptr;
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
    currentFrame = 0;
    Open(file);
}

Sprite::~Sprite()
{
    if (texture != nullptr)
    {
    }
}

void Sprite::Open(std::string file)
{
    if (texture != nullptr)
    {
    }

    texture = Resources::GetImage(file);

    if (texture != nullptr)
    {
        int texWidth, texHeight;
        SDL_QueryTexture(texture, nullptr, nullptr, &texWidth, &texHeight);

        width = texWidth / frameCountW;
        height = texHeight / frameCountH;

        SetClip(0, 0, width, height);
    }
}

void Sprite::SetClip(int x, int y, int w, int h)
{
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::SetFrame(int frame)
{
    currentFrame = frame;

    int currentX = (currentFrame % frameCountW) * width;
    int currentY = (currentFrame / frameCountW) * height;

    SetClip(currentX, currentY, width, height);
}

void Sprite::SetFrameCount(int frameCountW, int frameCountH)
{
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;

    if (texture != nullptr)
    {
        int texWidth, texHeight;
        SDL_QueryTexture(texture, nullptr, nullptr, &texWidth, &texHeight);

        width = texWidth / this->frameCountW;
        height = texHeight / this->frameCountH;

        currentFrame = 0;
        SetClip(0, 0, width, height);
    }
}

void Sprite::Render(int x, int y)
{
    if (texture != nullptr)
    {
        SDL_Rect dstRect;
        dstRect.x = x;
        dstRect.y = y;
        dstRect.w = clipRect.w;
        dstRect.h = clipRect.h;
        SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
    }
}

int Sprite::GetWidth() { return width; }
int Sprite::GetHeight() { return height; }
bool Sprite::IsOpen() { return texture != nullptr; }