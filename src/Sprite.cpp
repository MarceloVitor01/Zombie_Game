#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite(GameObject &associated) : Component(associated)
{
    texture = nullptr;
    width = 0;
    height = 0;
    frameCountW = 1;
    frameCountH = 1;
    currentFrame = 0;
    cameraFollower = false;
}

Sprite::Sprite(GameObject &associated, std::string file, int frameCountW, int frameCountH) : Component(associated)
{
    texture = nullptr;
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
    currentFrame = 0;
    cameraFollower = false;
    Open(file);
}

Sprite::~Sprite() {}

void Sprite::Open(std::string file)
{
    texture = Resources::GetImage(file);
    if (texture != nullptr)
    {
        int texWidth, texHeight;
        SDL_QueryTexture(texture, nullptr, nullptr, &texWidth, &texHeight);
        width = texWidth / frameCountW;
        height = texHeight / frameCountH;
        SetClip(0, 0, width, height);
        associated.box.w = width;
        associated.box.h = height;
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
        associated.box.w = width;
        associated.box.h = height;
    }
}

void Sprite::Render()
{
    Render(associated.box.x, associated.box.y);
}

void Sprite::Render(int x, int y)
{
    if (texture != nullptr)
    {
        SDL_Rect dstRect;
        dstRect.x = x - (cameraFollower ? 0 : Camera::pos.x);
        dstRect.y = y - (cameraFollower ? 0 : Camera::pos.y);
        dstRect.w = clipRect.w;
        dstRect.h = clipRect.h;
        SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
    }
}

int Sprite::GetWidth() { return width; }

int Sprite::GetHeight() { return height; }

bool Sprite::IsOpen() { return texture != nullptr; }

void Sprite::Update(float dt) {}

bool Sprite::Is(std::string type) { return type == "Sprite"; }

void Sprite::SetCameraFollower(bool follow)
{
    cameraFollower = follow;
}

bool Sprite::IsCameraFollower()
{
    return cameraFollower;
}