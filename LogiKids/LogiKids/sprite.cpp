#include "sprite.h"
#include "texture_manager.h"
#include "game.h"
#include <iostream>
#include <string>

Sprite::Sprite(const char* textureSheet, int xpos, int ypos)
{
	original_pos.x = xpos;
	original_pos.y = ypos;

	current_pos.x = original_pos.x;
    current_pos.y = original_pos.y;

	spriteTexture = TextureManager::loadTexture(textureSheet);

	SDL_QueryTexture(spriteTexture, NULL, NULL, &srcRect.w, &srcRect.h);
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
    
    w = destRect.w;
    h = destRect.h;
}

Sprite::~Sprite()
{
}

void Sprite::update()
{
    int x, y;

    if (grab) {
        SDL_GetMouseState(&x, &y);
        setPosition(x, y);

        destRect.x = x;
        destRect.y = y;
    }

}

void Sprite::render()
{
	SDL_RenderCopy(Game::renderer, spriteTexture, &srcRect, &destRect);
}

bool Sprite::handleEvent(SDL_Event* event){
    bool sprite_pressed = false;
    if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;

        if (x < current_pos.x)
        {
            inside = false;
        }
        else if (x > current_pos.x + w)
        {
            inside = false;
        }
        else if (y < current_pos.y)
        {
            inside = false;
        }
        else if (y > current_pos.y + h)
        {
            inside = false;
        }
        //if (!inside)
        //{
        //    currentSprite = BUTTON_SPRITE_MOUSE_OUT;
        //}
        //Mouse is inside button
        else
        {
            switch (event->type)
            {
            case SDL_MOUSEMOTION:
                printf("MOUSE MOTION\n");
                //currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;

            case SDL_MOUSEBUTTONDOWN:
                printf("MOUSE BUTTON DOWN\n");
                //currentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                sprite_pressed = true;
                grab = true;
                break;

            case SDL_MOUSEBUTTONUP:
                printf("MOUSE BUTTON UP\n");
                //currentSprite = BUTTON_SPRITE_MOUSE_UP;
                sprite_pressed = false;
                grab = false;
                break;
            }
        }
    }
    return sprite_pressed;

}

SDL_Point Sprite::getCurrentPosition(){
	return current_pos;
}

SDL_Point Sprite::getOriginalPosition(){
	return original_pos;
}

void Sprite::setPosition(int xpos, int ypos){
	current_pos.x = xpos;
	current_pos.y = ypos;
}

void Sprite::resetPosition(){
	current_pos = original_pos;
}

int Sprite::getWidth(){
	return w;
}

int Sprite::getHeight(){
	return h;
}
