#include "texture_manager.h"
#include "game.h"

SDL_Texture* TextureManager::loadTexture(const char* filename)
{
    SDL_Surface* tempSurface = IMG_Load(filename);
    if (!tempSurface) {
        printf("Unable to load image %s! SDL_image Error: %s\n", filename, IMG_GetError());
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return texture;
}

SDL_Surface* TextureManager::loadSurface(const char* filename)
{
    SDL_Surface* surface = IMG_Load(filename);
    if (!surface) {
        printf("Unable to load image %s! SDL_image Error: %s\n", filename, IMG_GetError());
    }
    return surface;
}

SDL_Color TextureManager::getPixelColor(SDL_Surface* pSurface, const int X, const int Y)
{
    int Bpp = pSurface->format->BytesPerPixel;
    Uint8* pPixel = (Uint8*)pSurface->pixels + Y * pSurface->pitch + X * Bpp;

    Uint32 PixelColor = *(Uint32*)pPixel;

    SDL_Color Color = { 0, 0, 0, 0 };

    SDL_GetRGBA(PixelColor, pSurface->format, &Color.r, &Color.g, &Color.b, &Color.a);

    return Color;
}

SDL_Texture* TextureManager::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(Game::gFont, textureText.c_str(), textColor);
    SDL_Texture* mTexture = nullptr;
   
    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        //Create texture from surface pixels
        SDL_Texture* mTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);

        if (mTexture == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }        

        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }
    return mTexture;
}
