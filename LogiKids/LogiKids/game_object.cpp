#include "game_object.h"
#include "texture_manager.h"

GameObject::GameObject(const char* textureSheet, int x, int y)
{
    objTexture = TextureManager::loadTexture(textureSheet);

    xpos = x;
    ypos = y;

    SDL_QueryTexture(objTexture, NULL, NULL, &srcRect.w, &srcRect.h);
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}

void GameObject::update()
{
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
}

void GameObject::render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

int GameObject::getXpos()
{
    return xpos;
}

int GameObject::getYpos()
{
    return ypos;
}

int GameObject::getHeight() {
    return destRect.h;
}

int GameObject::getWidth() {
    return destRect.w;
}
