#include "MainMenu.h"

MainMenu::MainMenu()
{
    clicked = false;
}

MainMenu::~MainMenu()
{
    clicked = false;
}

void MainMenu::Initialize(SDL_Renderer* ren)
{
    menuBackground.CreateTexture("Image/MainMenu.png", ren);
}

int MainMenu::EventHandling(SDL_Event& e)
{
    SDL_PollEvent(&e);
    switch (e.type)
    {
    case SDL_QUIT:
        return -1;
        break;
    case SDL_MOUSEBUTTONDOWN:
        if(e.motion.x > 285 && e.motion.x < 510 && e.motion.y > 470 && e.motion.y < 535)
        clicked = true;
    }
    return 0;
}

void MainMenu::Render(SDL_Renderer* ren)
{
    menuBackground.Render(ren);
}

bool MainMenu::getClicked()
{
    return clicked;
}
