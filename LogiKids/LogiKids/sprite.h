#pragma once
#include <SDL.h>
#include <SDL_image.h>

#define GRABBED 0
#define NONE 1
#define DROPPED 2

class Sprite
{
public:
	Sprite(const char* textureSheet, int xpos, int ypos);
	~Sprite();
	void update();
	void render();
	bool handleEvent(SDL_Event* event);
	SDL_Point getCurrentPosition();
	SDL_Point getOriginalPosition();
	void setPosition(int xpos, int ypos);
	void resetPosition();
	int getWidth();
	int getHeight();
	bool isGrabbed();
	bool dropped();
	bool grabbed();
	int grabEvent();
	void setGrabPosition(SDL_Point position);
	SDL_Point getGrabPosition();

private:
	SDL_Rect srcRect, destRect;
	SDL_Point original_pos;
	SDL_Point current_pos;
	SDL_Point grab_pos;
	int w;
	int h;
	SDL_Texture* spriteTexture;
	bool grab = false;
	bool lastGrabState = false; // false = not dropped, true = dropped
	bool lastDropState = true;

};

