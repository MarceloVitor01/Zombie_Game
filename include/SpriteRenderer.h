#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "Component.h"
#include "Sprite.h"
#include <string>

class SpriteRenderer : public Component
{
public:
    SpriteRenderer(GameObject &associated, std::string file, int frameCountW = 1, int frameCountH = 1);
    ~SpriteRenderer();

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

    void SetFrame(int frame);

private:
    Sprite sprite;
};

#endif