#include "text_texture.h"
#include "game.h"

void TextTexture::loadText(std::string text, SDL_Color textColor, TTF_Font* font, int font_size)
{
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), textColor);
    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
        if (texture == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            //Get image dimensions
            width = textSurface->w;
            height = textSurface->h;
        }
        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }

    SDL_QueryTexture(texture, NULL, NULL, &srcRect.w, &srcRect.h);

    // Setup for Source and Destination Rectangles for rendering
    //destRect.x = xpos;
    //destRect.y = ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;

    //srcRect.x = 0;
    //srcRect.y = 0;

    //width = destRect.w;
    //height = destRect.h;

    //Return success
    //return mTexture != NULL;
}

TextTexture::TextTexture(std::string text, SDL_Color textColor, TTF_Font* font, int font_size, int xpos, int ypos)
{
    loadText(text, textColor, font, font_size);
    // Setup for Source and Destination Rectangles for rendering
    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;

    srcRect.x = 0;
    srcRect.y = 0;

    width = destRect.w;
    height = destRect.h;
}

void TextTexture::setPositon(int xpos, int ypos)
{
    destRect.x = xpos;
    destRect.y = ypos;
}

void TextTexture::render()
{
    SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
}

void TextTexture::setColor(SDL_Color color)
{
    SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
}

TextTexture::~TextTexture()
{
}