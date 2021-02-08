#include "texture_manager.h"
#include "game.h"
#include "button.h"
#include <iostream>
#include <string>

Button::Button(const char* textureSheet, int xpos, int ypos)
{
    topPosition.x = xpos;
    topPosition.y = ypos;
    

    currentSprite = BUTTON_SPRITE_MOUSE_OUT;

    spriteClips[BUTTON_SPRITE_MOUSE_OUT] = TextureManager::loadTexture(appendFilenameToPath(textureSheet, "_0.png").c_str());// filename.c_str());
    spriteClips[BUTTON_SPRITE_MOUSE_OVER_MOTION] = TextureManager::loadTexture(appendFilenameToPath(textureSheet, "_1.png").c_str());
    spriteClips[BUTTON_SPRITE_MOUSE_DOWN] = TextureManager::loadTexture(appendFilenameToPath(textureSheet, "_2.png").c_str());
    spriteClips[BUTTON_SPRITE_MOUSE_UP] = TextureManager::loadTexture(appendFilenameToPath(textureSheet, "_3.png").c_str());
    spriteClips[BUTTON_SPRITE_TOTAL] = TextureManager::loadTexture(appendFilenameToPath(textureSheet, "_4.png").c_str());
    
    SDL_QueryTexture(spriteClips[BUTTON_SPRITE_MOUSE_OUT], NULL, NULL, &srcRect.w, &srcRect.h);

    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
    h = destRect.h;
    w = destRect.w;
}

Button::~Button(){}

std::string Button::appendFilenameToPath(const char* textureSheet, const char* path)
{
    std::string filename = "assets/buttons/";
    filename += textureSheet;
    filename += path; 
    return filename;
}

void Button::setPosition(int x, int y)
{
    topPosition.x = x;
    topPosition.y = y;
}

void Button::setSize(int h, int w)
{
    this->h = h;
    this->w = w;
}

button_sprite Button::currentState()
{
    return currentSprite;
}

bool Button::handleEvent(SDL_Event* e)
{
    bool button_pressed = false;
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;

        //Mouse is left of the button
        if (x < topPosition.x)
        {
            inside = false;
        }
        //Mouse is right of the button
        else if (x > topPosition.x + w)
        {
            inside = false;
        }
        //Mouse above the button
        else if (y < topPosition.y)
        {
            inside = false;
        }
        //Mouse below the button
        else if (y > topPosition.y + h)
        {
            inside = false;
        }
        //Mouse is outside button
        if (!inside)
        {
            currentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        //Mouse is inside button
        else
        {
            switch (e->type)
            {
            case SDL_MOUSEMOTION:
                //printf("MOUSE MOTION\n");
                currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;

            case SDL_MOUSEBUTTONDOWN:
                printf("MOUSE BUTTON DOWN\n");
                currentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                button_pressed = true;
                break;

            case SDL_MOUSEBUTTONUP:
                printf("MOUSE BUTTON UP\n");
                currentSprite = BUTTON_SPRITE_MOUSE_UP;
                button_pressed = false;
                break;
            }
        }
    }
    return button_pressed;
}

void Button::render()
{
    //Show current button sprite
    SDL_RenderCopy(Game::renderer, spriteClips[currentSprite], &srcRect, &destRect);
}
