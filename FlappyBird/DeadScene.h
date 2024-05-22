#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Background.h"

class DeadScene
{
private:
    bool clicked;
    Background deadBackground;
public:
    DeadScene();
    ~DeadScene();
    void Initialize(SDL_Renderer* ren);
    int EventHandling(SDL_Event& e);
    void Render(SDL_Renderer* ren);
    bool getClicked();
    void setClicked();
};
