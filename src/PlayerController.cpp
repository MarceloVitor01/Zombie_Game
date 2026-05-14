#include "PlayerController.h"
#include "Character.h"
#include "InputManager.h"
#include "Camera.h"

PlayerController::PlayerController(GameObject &associated) : Component(associated) {}

void PlayerController::Update(float dt)
{
    InputManager &input = InputManager::GetInstance();
    Character *character = associated.GetComponent<Character>();

    if (!character)
        return;

    Vec2 dir(0, 0);
    if (input.IsKeyDown(SDLK_w))
        dir.y -= 1;
    if (input.IsKeyDown(SDLK_s))
        dir.y += 1;
    if (input.IsKeyDown(SDLK_a))
        dir.x -= 1;
    if (input.IsKeyDown(SDLK_d))
        dir.x += 1;

    character->Issue(Command(MOVE, dir.x, dir.y));

    if (input.MousePress(LEFT_MOUSE_BUTTON))
    {
        float mouseX = input.GetMouseX() + Camera::pos.x;
        float mouseY = input.GetMouseY() + Camera::pos.y;
        character->Issue(Command(SHOOT, mouseX, mouseY));
    }
}

void PlayerController::Render() {}

bool PlayerController::Is(std::string type)
{
    return type == "PlayerController";
}