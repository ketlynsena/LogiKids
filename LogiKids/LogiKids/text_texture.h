#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>

class TextTexture
{
public:
    TextTexture(std::string text, SDL_Color textColor, TTF_Font* font, int font_size, int xpos, int ypos);
    ~TextTexture();
    void setPositon(int xpos, int ypos);
    void render();
    void setColor(SDL_Color color);
    void loadText(std::string text, SDL_Color textColor, TTF_Font* font, int font_size);

private:
	SDL_Texture* texture;
    int width, height;
    SDL_Rect destRect;
    SDL_Rect srcRect;
    
};

