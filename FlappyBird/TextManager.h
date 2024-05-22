#pragma once

#include <string>
#include <SDL_ttf.h>
#include <iostream>

class TextManager
{
private:

    TTF_Font* font;
    SDL_Rect textRect;
    SDL_Texture* fontTexture;
public:
    void CreateFont(const char* filename, int size);
    void Text(std::string text, int r, int g, int b, SDL_Renderer* ren);
    void CreateTexture(SDL_Surface* surface, SDL_Renderer* ren);
    void Render(SDL_Renderer* ren, int x, int y);
    void CloseFont();
};
