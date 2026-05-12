#include "Camera.h"
#include "InputManager.h"
#include "Game.h"

GameObject *Camera::focus = nullptr;
Vec2 Camera::pos(0, 0);
Vec2 Camera::speed(300, 300);

void Camera::Follow(GameObject *newFocus)
{
    focus = newFocus;
}

void Camera::Unfollow()
{
    focus = nullptr;
}

void Camera::Update(float dt)
{
    if (focus != nullptr)
    {
        int w, h;
        SDL_GetRendererOutputSize(Game::GetInstance().GetRenderer(), &w, &h);
        pos.x = focus->box.x + (focus->box.w / 2.0f) - (w / 2.0f);
        pos.y = focus->box.y + (focus->box.h / 2.0f) - (h / 2.0f);
    }
    else
    {
        InputManager &input = InputManager::GetInstance();

        if (input.IsKeyDown(LEFT_ARROW_KEY))
        {
            pos.x -= speed.x * dt;
        }
        if (input.IsKeyDown(RIGHT_ARROW_KEY))
        {
            pos.x += speed.x * dt;
        }
        if (input.IsKeyDown(UP_ARROW_KEY))
        {
            pos.y -= speed.y * dt;
        }
        if (input.IsKeyDown(DOWN_ARROW_KEY))
        {
            pos.y += speed.y * dt;
        }
    }
}