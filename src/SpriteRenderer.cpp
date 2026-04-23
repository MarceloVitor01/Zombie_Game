#include "SpriteRenderer.h"
#include "GameObject.h"

SpriteRenderer::SpriteRenderer(GameObject &associated, std::string file, int frameCountW, int frameCountH)
    : Component(associated), sprite(file, frameCountW, frameCountH)
{
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
}

SpriteRenderer::~SpriteRenderer() {}

void SpriteRenderer::Update(float dt) {}

void SpriteRenderer::Render()
{
    sprite.Render(associated.box.x, associated.box.y);
}

bool SpriteRenderer::Is(std::string type)
{
    return type == "SpriteRenderer";
}

void SpriteRenderer::SetFrame(int frame)
{
    sprite.SetFrame(frame);
}