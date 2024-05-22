#include "Collision.h"

bool CollisionManager::haveCollision(SDL_Rect* a, SDL_Rect* b)
{
    SDL_bool check = SDL_HasIntersection(a, b);
    if(check)
    {
        return true;
    }
    else
    {
        return false;
    }
}
