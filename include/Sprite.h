#ifndef SPRITE_H
#define SPRITE_H

#include "Component.h"
#include "SDL_include.h"
#include <string>

class Sprite : public Component
{
public:
    Sprite(GameObject &associated);
    Sprite(GameObject &associated, std::string file, int frameCountW = 1, int frameCountH = 1);
    ~Sprite();

    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void SetFrame(int frame);
    void SetFrameCount(int frameCountW, int frameCountH);

    void Render() override;
    void Render(int x, int y);

    int GetWidth();
    int GetHeight();
    bool IsOpen();

    void Update(float dt) override;
    bool Is(std::string type) override;

    void SetCameraFollower(bool follow);
    bool IsCameraFollower();

private:
    SDL_Texture *texture;
    int width;
    int height;
    SDL_Rect clipRect;
    int frameCountW;
    int frameCountH;
    int currentFrame;
    bool cameraFollower;
};

#endif