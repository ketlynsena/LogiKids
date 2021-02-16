#pragma once
#ifndef TEXTURE_MANAGER_H_INCLUDED
#define TEXTURE_MANAGER_H_INCLUDED

#include "game.h"

class TextureManager
{
public:
    static SDL_Texture* loadTexture(const char* filename);
    static SDL_Surface* loadSurface(const char* filename);
    SDL_Color   getPixelColor(SDL_Surface* pSurface, const int X, const int Y);
    static SDL_Texture* loadFromRenderedText(std::string textureText, SDL_Color textColor);
};

#endif // TEXTURE_MANAGER_H_INCLUDED
