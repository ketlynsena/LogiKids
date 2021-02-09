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
