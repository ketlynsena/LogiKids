#include "game_object.h"
#include "texture_manager.h"

GameObject::GameObject(const char* textureSheet, int x, int y)
{
    objTexture = TextureManager::loadTexture(textureSheet);

    xpos = x;
    ypos = y;

    //srcRect.h = objTexture->h;//600;
    SDL_QueryTexture(objTexture, NULL, NULL, &srcRect.w, &srcRect.h);
    //srcRect.w = objTexture->w;//800;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}

void GameObject::update()
{
    //can update position

    //srcRect.h = 800;
    //srcRect.w = 600;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    //destRect.w = srcRect.w;
    //destRect.h = srcRect.h;
}

void GameObject::render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
