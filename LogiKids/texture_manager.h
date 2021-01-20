#ifndef TEXTURE_MANAGER_H_INCLUDED
#define TEXTURE_MANAGER_H_INCLUDED

#include "game.h"

class TextureManager
{
public:
    static SDL_Texture* loadTexture(const char* filename);
};

#endif // TEXTURE_MANAGER_H_INCLUDED
