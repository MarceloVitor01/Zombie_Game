#include "Collider.h"
#include "GameObject.h"
#include "Camera.h"
#include "Game.h"

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset) : Component(associated)
{
    this->scale = scale;
    this->offset = offset;
}

void Collider::Update(float dt)
{
    box.w = associated.box.w * scale.x;
    box.h = associated.box.h * scale.y;
    Vec2 center = associated.box.Center();
    Vec2 rotatedOffset = offset.GetRotated(associated.angleDeg * M_PI / 180.0f);
    box.SetCenter(center.x + rotatedOffset.x, center.y + rotatedOffset.y);
}

void Collider::Render()
{
    Vec2 center(box.Center().x, box.Center().y);
    SDL_Point points[5];
    Vec2 point = (Vec2(box.x, box.y) - center).GetRotated(associated.angleDeg * M_PI / 180.0f) + center - Camera::pos;
    points[0] = {(int)point.x, (int)point.y};
    points[4] = {(int)point.x, (int)point.y};
    point = (Vec2(box.x + box.w, box.y) - center).GetRotated(associated.angleDeg * M_PI / 180.0f) + center - Camera::pos;
    points[1] = {(int)point.x, (int)point.y};
    point = (Vec2(box.x + box.w, box.y + box.h) - center).GetRotated(associated.angleDeg * M_PI / 180.0f) + center - Camera::pos;
    points[2] = {(int)point.x, (int)point.y};
    point = (Vec2(box.x, box.y + box.h) - center).GetRotated(associated.angleDeg * M_PI / 180.0f) + center - Camera::pos;
    points[3] = {(int)point.x, (int)point.y};
    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
}

bool Collider::Is(std::string type)
{
    return type == "Collider";
}

void Collider::SetScale(Vec2 scale)
{
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset)
{
    this->offset = offset;
}