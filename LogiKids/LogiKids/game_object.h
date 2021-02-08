#pragma once
#ifndef GAME_OBJECT_H_INCLUDED
#define GAME_OBJECT_H_INCLUDED

#include "game.h"

class GameObject
{
public:
    GameObject(const char* textureSheet, int x, int y);
    ~GameObject();

    void update();
    void render();
    int getXpos();
    int getYpos();
    int getHeight();
    int getWidth();

private:
    int xpos;
    int ypos;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
};

#endif // GAME_OBJECT_H_INCLUDED
