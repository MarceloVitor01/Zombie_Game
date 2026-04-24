#include "Sound.h"
#include "Resources.h"

Sound::Sound()
{
    chunk = nullptr;
    channel = -1;
}

Sound::Sound(std::string file) : Sound()
{
    Open(file);
}

Sound::~Sound()
{
    if (chunk != nullptr)
    {
        Mix_HaltChannel(channel);
    }
}

void Sound::Play(int times)
{
    if (chunk != nullptr)
    {
        channel = Mix_PlayChannel(-1, chunk, times - 1);
    }
}

void Sound::Stop()
{
    if (chunk != nullptr && channel != -1)
    {
        Mix_HaltChannel(channel);
    }
}

void Sound::Open(std::string file)
{
    chunk = Resources::GetSound(file);
}

bool Sound::IsOpen()
{
    return chunk != nullptr;
}