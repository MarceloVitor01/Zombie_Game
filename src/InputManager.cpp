#include "InputManager.h"

InputManager &InputManager::GetInstance()
{
    static InputManager instance;
    return instance;
}

InputManager::InputManager()
{
    for (int i = 0; i < 6; i++)
    {
        mouseState[i] = false;
        mouseUpdate[i] = 0;
    }
    for (int i = 0; i < 416; i++)
    {
        keyState[i] = false;
        keyUpdate[i] = 0;
    }
    quitRequested = false;
    updateCounter = 0;
    mouseX = 0;
    mouseY = 0;
}

InputManager::~InputManager() {}

void InputManager::Update()
{
    SDL_Event event;
    SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;
    updateCounter++;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            quitRequested = true;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
        {
            int button = event.button.button;
            bool state = (event.type == SDL_MOUSEBUTTONDOWN);

            if (button < 6)
            {
                mouseState[button] = state;
                mouseUpdate[button] = updateCounter;
            }
        }

        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        {
            if (!event.key.repeat)
            {
                int key = event.key.keysym.sym;
                if (key >= 0x40000000 && key <= 0x4000011A)
                {
                    key -= 0x3FFFFF81;
                }

                bool state = (event.type == SDL_KEYDOWN);
                if (key >= 0 && key < 416)
                {
                    keyState[key] = state;
                    keyUpdate[key] = updateCounter;
                }
            }
        }
    }
}

bool InputManager::KeyPress(int key)
{
    if (key >= 0x40000000 && key <= 0x4000011A)
        key -= 0x3FFFFF81;
    if (key < 0 || key >= 416)
        return false;
    return (keyState[key] && keyUpdate[key] == updateCounter);
}

bool InputManager::KeyRelease(int key)
{
    if (key >= 0x40000000 && key <= 0x4000011A)
        key -= 0x3FFFFF81;
    if (key < 0 || key >= 416)
        return false;
    return (!keyState[key] && keyUpdate[key] == updateCounter);
}

bool InputManager::IsKeyDown(int key)
{
    if (key >= 0x40000000 && key <= 0x4000011A)
        key -= 0x3FFFFF81;
    if (key < 0 || key >= 416)
        return false;
    return keyState[key];
}

bool InputManager::MousePress(int button)
{
    if (button < 0 || button >= 6)
        return false;
    return (mouseState[button] && mouseUpdate[button] == updateCounter);
}

bool InputManager::MouseRelease(int button)
{
    if (button < 0 || button >= 6)
        return false;
    return (!mouseState[button] && mouseUpdate[button] == updateCounter);
}

bool InputManager::IsMouseDown(int button)
{
    if (button < 0 || button >= 6)
        return false;
    return mouseState[button];
}

int InputManager::GetMouseX() { return mouseX; }

int InputManager::GetMouseY() { return mouseY; }

bool InputManager::QuitRequested() { return quitRequested; }