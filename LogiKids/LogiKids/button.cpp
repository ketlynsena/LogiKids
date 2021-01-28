#include "game_object.h"
#include "button.h"

Button::Button()
{
    topPosition.x = 0;
    topPosition.y = 0;
    h = 38;
    w = 38;

    currentSprite = BUTTON_SPRITE_MOUSE_OUT;
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

void Button::handleEvent(SDL_Event* e)
{
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
        else if (x > topPosition.x + w)//BUTTON_WIDTH )
        {
            inside = false;
        }
        //Mouse above the button
        else if (y < topPosition.y)
        {
            inside = false;
        }
        //Mouse below the button
        else if (y > topPosition.y + h)//BUTTON_HEIGHT )
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
                currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;

            case SDL_MOUSEBUTTONDOWN:
                currentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;

            case SDL_MOUSEBUTTONUP:
                currentSprite = BUTTON_SPRITE_MOUSE_UP;
                break;
            }
        }
    }
}

//void Button::render()
//{
    //Show current button sprite
    //gButtonSpriteSheetTexture.render( topPosition.x, topPosition.y, &gSpriteClips[ currentSprite ] );
//}
