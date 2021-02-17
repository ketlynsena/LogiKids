#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

#define N_MOUSE_STATES 4

// Grab and Drop options
#define GRABBED 0
#define NONE 1
#define DROPPED 2

enum sprite_state
{
	MOUSE_OUT = 0,
	MOUSE_OVER_MOTION = 1,
	MOUSE_DOWN = 2,
	MOUSE_UP = 3
};

class GameTexture
{
public:
	GameTexture(const char* textureSheet, int xpos, int ypos, bool hasClips, bool isMovable);
	SDL_Texture* loadTexture(const char* textureSheet);
	std::string appendFilenameToPath(const char* textureSheet, const char* path);
	~GameTexture();
	void updatePosFromMouseState();
	void setPosition(int xpos, int ypos);
	void resetPosition();
	void setColor(SDL_Color color);
	void resetColor();
	void render();
	int getWidth();
	int getHeight();
	SDL_Point getOriginalPosition();
	SDL_Point getCurrentPosition();
	bool isGrabbed();
	SDL_Point getGrabPosition();
	bool dropped();
	bool grabbed();
	void setGrabPosition(SDL_Point position);
	bool handleEvent(SDL_Event* event);
	SDL_Color getPixelColor(const int X, const int Y);
	bool isWithinBoundaries();

private:
	SDL_Texture* spriteTexture;
	SDL_Texture* spriteClips[4];
	SDL_Surface* spriteSurface = nullptr;
	SDL_Rect	 srcRect, destRect;
	SDL_Point	 originalPosition, grabPosition;
	sprite_state currentSprite = MOUSE_OUT;
	int			 height, width;
	bool		 grab = false, lastGrabState = false, lastDropState = true;
	bool		 withinBoudaries = false;
	bool		 isMovable = false, hasClips = false;


};