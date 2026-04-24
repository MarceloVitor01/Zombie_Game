#include "Resources.h"
#include "Game.h"
#include <iostream>

std::unordered_map<std::string, SDL_Texture *> Resources::imageTable;
std::unordered_map<std::string, Mix_Music *> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk *> Resources::soundTable;

SDL_Texture *Resources::GetImage(std::string file)
{
    auto it = imageTable.find(file);
    if (it != imageTable.end())
    {
        return it->second;
    }

    SDL_Texture *texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (texture != nullptr)
    {
        imageTable[file] = texture;
    }
    return texture;
}

void Resources::ClearImages()
{
    for (auto &item : imageTable)
    {
        SDL_DestroyTexture(item.second);
    }
    imageTable.clear();
}

Mix_Music *Resources::GetMusic(std::string file)
{
    auto it = musicTable.find(file);
    if (it != musicTable.end())
    {
        return it->second;
    }

    Mix_Music *music = Mix_LoadMUS(file.c_str());
    if (music != nullptr)
    {
        musicTable[file] = music;
    }
    return music;
}

void Resources::ClearMusics()
{
    for (auto &item : musicTable)
    {
        Mix_FreeMusic(item.second);
    }
    musicTable.clear();
}

Mix_Chunk *Resources::GetSound(std::string file)
{
    auto it = soundTable.find(file);
    if (it != soundTable.end())
    {
        return it->second;
    }

    Mix_Chunk *chunk = Mix_LoadWAV(file.c_str());
    if (chunk != nullptr)
    {
        soundTable[file] = chunk;
    }
    return chunk;
}

void Resources::ClearSounds()
{
    for (auto &item : soundTable)
    {
        Mix_FreeChunk(item.second);
    }
    soundTable.clear();
}