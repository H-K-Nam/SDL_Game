#include "DeadScene.h"

DeadScene::DeadScene()
{
    clicked = false;
}

DeadScene::~DeadScene()
{
    clicked = false;
}

void DeadScene::Initialize(SDL_Renderer* ren)
{
    deadBackground.CreateTexture("Image/deadBackground.png", ren);
}

int DeadScene::EventHandling(SDL_Event& e)
{
    SDL_PollEvent(&e);
    switch (e.type)
    {
    case SDL_QUIT:
        return -1;
        break;
    case SDL_MOUSEBUTTONDOWN:
        if(e.motion.x > 263 && e.motion.x < 537 && e.motion.y > 262 && e.motion.y < 347)
        clicked = true;
    }
    return 0;
}

void DeadScene::Render(SDL_Renderer* ren)
{
    deadBackground.Render(ren);
}

bool DeadScene::getClicked()
{
    return clicked;
}

void DeadScene::setClicked()
{
    clicked = false;
}
