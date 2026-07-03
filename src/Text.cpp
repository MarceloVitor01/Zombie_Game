#include "Text.h"
#include "Game.h"
#include "Camera.h"
#include <iostream>

Text::Text(GameObject &associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color)
    : Component(associated), font(nullptr), texture(nullptr), text(text), style(style), fontFile(fontFile), fontSize(fontSize), color(color)
{
    RemakeTexture();
}

Text::~Text()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }
    if (font != nullptr)
    {
        TTF_CloseFont(font);
    }
}

void Text::Update(float dt)
{
}

void Text::Render()
{
    if (texture != nullptr)
    {
        SDL_Rect clipRect = {0, 0, (int)associated.box.w, (int)associated.box.h};
        SDL_Rect dstRect = {(int)(associated.box.x - Camera::pos.x), (int)(associated.box.y - Camera::pos.y), clipRect.w, clipRect.h};

        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
    }
}

bool Text::Is(std::string type)
{
    return type == "Text";
}

void Text::SetText(std::string text)
{
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color)
{
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style)
{
    this->style = style;
    RemakeTexture();
}

void Text::SetFontFile(std::string fontFile)
{
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize)
{
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    if (font != nullptr)
    {
        TTF_CloseFont(font);
        font = nullptr;
    }

    font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (font == nullptr)
    {
        std::cout << "Erro ao carregar fonte: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Surface *surface = nullptr;

    if (style == SOLID)
    {
        surface = TTF_RenderText_Solid(font, text.c_str(), color);
    }
    else if (style == SHADED)
    {
        SDL_Color bg = {0, 0, 0, 255}; // Fundo preto para o shaded
        surface = TTF_RenderText_Shaded(font, text.c_str(), color, bg);
    }
    else if (style == BLENDED)
    {
        surface = TTF_RenderText_Blended(font, text.c_str(), color);
    }

    if (surface != nullptr)
    {
        texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
        associated.box.w = surface->w;
        associated.box.h = surface->h;
        SDL_FreeSurface(surface);
    }
}