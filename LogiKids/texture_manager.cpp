#include "texture_manager.h"

SDL_Texture* TextureManager::loadTexture(const char* filename)
{
    SDL_Surface* tempSurface = IMG_Load(filename);
    if(!tempSurface){
        printf( "Unable to load image %s! SDL_image Error: %s\n", filename, IMG_GetError() );
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return texture;
}
