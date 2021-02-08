#pragma once
#ifndef TEXTURE_MANAGER_H_INCLUDED
#define TEXTURE_MANAGER_H_INCLUDED

#include "game.h"

class TextureManager
{
public:
    static SDL_Texture* loadTexture(const char* filename);
    static SDL_Texture* loadFromRenderedText(std::string textureText, SDL_Color textColor);
};

#endif // TEXTURE_MANAGER_H_INCLUDED
