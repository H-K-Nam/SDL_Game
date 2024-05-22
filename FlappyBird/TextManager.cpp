#include "TextManager.h"

void TextManager::CreateFont(const char* filename, int size)
{
    font = TTF_OpenFont(filename, size);
    if(!font)
    {
        std::cerr << TTF_GetError() << std::endl;
    }
}

void TextManager::Text(std::string text, int r, int g, int b, SDL_Renderer* ren)
{
    char* text1 = new char[text.size()+1];
    std::copy(text.begin(), text.end(), text1);
    text1[text.size()] = '\0';
    SDL_Color color = {r, g, b, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text1, color);
    if(textSurface == NULL)
    {
        std::cerr << TTF_GetError() << std::endl;
    }
    CreateTexture(textSurface, ren);
    SDL_FreeSurface(textSurface);
    delete text1;
    text1 = 0;
}

void TextManager::CreateTexture(SDL_Surface* surface, SDL_Renderer* ren)
{
    fontTexture = SDL_CreateTextureFromSurface(ren, surface);
}

void TextManager::Render(SDL_Renderer* ren, int x, int y)
{
    textRect.x = x; textRect.y=y;
    SDL_QueryTexture(fontTexture, NULL, NULL, &textRect.w, &textRect.h);
    SDL_RenderCopy(ren, fontTexture, NULL, &textRect);
}

void TextManager::CloseFont()
{
    TTF_CloseFont(font);
}
