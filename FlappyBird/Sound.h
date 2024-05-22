#pragma once

#include <SDL.h>
#include <iostream>
#include <string>
#include <SDL_mixer.h>
#include <unordered_map>

class SoundManager
{
private:
    std::unordered_map<std::string, Mix_Music*> gMusic;
    std::unordered_map<std::string, Mix_Chunk*> gSound;
public:
    SoundManager();
    ~SoundManager();
    void Init();
    void Close();
    void loadSound(const std::string& id, const std::string& filename);
    void loadMusic(const std::string& id, const std::string& filename);
    void playSound(const std::string& id);
    void playMusic(const std::string& id);
    void stopMusic();
    void freeMusic(const std::string& id);
    void freeSound(const std::string& id);
};
