#include "Sound.h"

SoundManager::SoundManager() {};

SoundManager::~SoundManager()
{
    Close();
}

void SoundManager::Init()
{
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << Mix_GetError() << std::endl;
    }
}

void SoundManager::Close()
{
    for(auto& sound: gSound)
    {
        Mix_FreeChunk(sound.second);
    }
    gSound.clear();

    for(auto& music: gMusic)
    {
        Mix_FreeMusic(music.second);
    }
    gMusic.clear();
}

void SoundManager::loadSound(const std::string& id, const std::string& filename)
{
    Mix_Chunk* sound = Mix_LoadWAV(filename.c_str());
    if(sound == nullptr)
    {
        std::cerr << Mix_GetError() << std::endl;
    }
    gSound[id] = sound;
}

void SoundManager::loadMusic(const std::string& id, const std::string& filename)
{
    Mix_Music* music = Mix_LoadMUS(filename.c_str());
    if(music == nullptr)
    {
        std::cerr << Mix_GetError() << std::endl;
    }
    gMusic[id] = music;
}

void SoundManager::playSound(const std::string& id)
{
    if(gSound.find(id) != gSound.end())
    {
        Mix_PlayChannel(-1, gSound[id], 0);
    }
    else
    {
        std::cerr << "Sound ID not found: " << id << std::endl;
    }
}

void SoundManager::playMusic(const std::string& id)
{
    if(gMusic.find(id) != gMusic.end())
    {
        Mix_PlayMusic(gMusic[id], -1);
    }
    else
    {
        std::cerr << "Music ID not found: " << id << std::endl;
    }
}

void SoundManager::stopMusic()
{
    Mix_HaltMusic();
}

void SoundManager::freeMusic(const std::string& id)
{
    Mix_FreeMusic(gMusic[id]);
}

void SoundManager::freeSound(const std::string& id)
{
    Mix_FreeChunk(gSound[id]);
}
