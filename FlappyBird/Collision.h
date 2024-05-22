#pragma once
#include <SDL.h>
#include <SDL_image.h>

class CollisionManager
{
public:
    static bool haveCollision(SDL_Rect* a, SDL_Rect* b);
};
