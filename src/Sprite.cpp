#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"
#include "GameObject.h"

Sprite::Sprite(GameObject &associated) : Component(associated)
{
    texture = nullptr;
    width = 0;
    height = 0;
    frameCountW = 1;
    frameCountH = 1;
    currentFrame = 0;
    cameraFollower = false;
    scale = Vec2(1.0f, 1.0f);
    flip = SDL_FLIP_NONE;
}

Sprite::Sprite(GameObject &associated, std::string file, int frameCountW, int frameCountH) : Component(associated)
{
    texture = nullptr;
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
    currentFrame = 0;
    cameraFollower = false;
    scale = Vec2(1.0f, 1.0f);
    flip = SDL_FLIP_NONE;
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
        associated.box.w = width * scale.x;
        associated.box.h = height * scale.y;
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
        associated.box.w = width * scale.x;
        associated.box.h = height * scale.y;
    }
}

void Sprite::Render()
{
    int renderX = associated.box.x - (cameraFollower ? 0 : Camera::pos.x);
    int renderY = associated.box.y - (cameraFollower ? 0 : Camera::pos.y);
    Render(renderX, renderY);
}

void Sprite::Render(int x, int y)
{
    if (texture != nullptr)
    {
        SDL_Rect dstRect;
        dstRect.x = x;
        dstRect.y = y;
        dstRect.w = clipRect.w * scale.x;
        dstRect.h = clipRect.h * scale.y;

        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, associated.angleDeg, nullptr, flip);
    }
}

int Sprite::GetWidth() { return width * scale.x; }

int Sprite::GetHeight() { return height * scale.y; }

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

void Sprite::SetScale(float scaleX, float scaleY)
{
    if (scaleX != 0 && scaleY != 0)
    {
        scale.x = scaleX;
        scale.y = scaleY;
        Vec2 center = associated.box.Center();
        associated.box.w = width * scale.x;
        associated.box.h = height * scale.y;
        associated.box.SetCenter(center);
    }
}

Vec2 Sprite::GetScale()
{
    return scale;
}

void Sprite::SetFlip(SDL_RendererFlip flip)
{
    this->flip = flip;
}