#pragma once
#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>

enum button_sprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

class Button
{
public:
    Button(const char* textureSheet, int xpos, int ypos);
    ~Button();
    void setPosition(int x, int y);
    void setSize(int h, int w);
    void handleEvent(SDL_Event* e);
    button_sprite currentState();
    void render();

private:
    SDL_Point topPosition; //Top left position
    button_sprite currentSprite;
    int w;
    int h;

    SDL_Texture* spriteClips[5];
    SDL_Rect srcRect, destRect;
};


#endif // BUTTON_H_INCLUDED
