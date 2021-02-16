#include "game_texture.h"
#include "game.h"

GameTexture::GameTexture(const char* textureSheet, int xpos, int ypos, bool hasClips, bool isMovable)
{
	if (isMovable)
	{
		this->isMovable = true;
	}
	
	if (hasClips) // if texture has many clips
	{	
		this->hasClips = true;
		spriteClips[MOUSE_OUT]		   = loadTexture(appendFilenameToPath(textureSheet, "_0.png").c_str());
		spriteClips[MOUSE_OVER_MOTION] = loadTexture(appendFilenameToPath(textureSheet, "_1.png").c_str());
		spriteClips[MOUSE_DOWN]		   = loadTexture(appendFilenameToPath(textureSheet, "_2.png").c_str());
		spriteClips[MOUSE_UP]		   = loadTexture(appendFilenameToPath(textureSheet, "_3.png").c_str());

		// Default texture is MOUSE_OUT
		spriteTexture = spriteClips[MOUSE_OUT];
		spriteSurface = IMG_Load(appendFilenameToPath(textureSheet, "_0.png").c_str());
	}
	else 
	{
		spriteTexture = loadTexture(textureSheet);
		spriteSurface = IMG_Load(textureSheet);
	}
	
	SDL_QueryTexture(spriteTexture, NULL, NULL, &srcRect.w, &srcRect.h);
	
	// Setup for Source and Destination Rectangles for rendering
	originalPosition.x = xpos;
	originalPosition.y = ypos;

	destRect.x		   = xpos;
	destRect.y		   = ypos;
	destRect.w		   = srcRect.w;
	destRect.h		   = srcRect.h;

	srcRect.x		   = 0;
	srcRect.y		   = 0;

	width			   = destRect.w;
	height			   = destRect.h;
}

SDL_Texture* GameTexture::loadTexture(const char* textureSheet)
{
	SDL_Surface* tempSurface = IMG_Load(textureSheet);
	if (!tempSurface)
		printf("Unable to load image %s - SDL_image Error: %s\n", textureSheet, IMG_GetError());
	
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return texture;
}

std::string GameTexture::appendFilenameToPath(const char* textureSheet, const char* path)
{
	std::string filename; //= "assets/buttons/";
	filename += textureSheet;
	filename += path;
	return filename;
}

GameTexture::~GameTexture()
{
	SDL_FreeSurface(spriteSurface);
}

void GameTexture::updatePosFromMouseState()
{
	int x, y;

	if (grab) {
		SDL_GetMouseState(&x, &y);
		setPosition(x - (width / 2), y - (height / 2));
	}
}

void GameTexture::setPosition(int xpos, int ypos) {
	destRect.x = xpos;
	destRect.y = ypos;
}

void GameTexture::resetPosition() {
	destRect.x = originalPosition.x;
	destRect.y = originalPosition.y;
}

void GameTexture::render()
{
	if(hasClips)
		SDL_RenderCopy(Game::renderer, spriteClips[currentSprite], &srcRect, &destRect);
	else		
		SDL_RenderCopy(Game::renderer, spriteTexture, &srcRect, &destRect);
}

int GameTexture::getWidth() {
	return width;
}

int GameTexture::getHeight() {
	return height;
}

SDL_Point GameTexture::getOriginalPosition() {
	return originalPosition;
}

SDL_Point GameTexture::getCurrentPosition() {
	SDL_Point currentPosition;
	currentPosition.x = destRect.x;
	currentPosition.y = destRect.y;
	return currentPosition;
}

bool GameTexture::isGrabbed()
{
	return grab;
}

SDL_Point GameTexture::getGrabPosition()
{
	return grabPosition;
}

bool GameTexture::dropped()
{
	if (grab == true) {
		lastGrabState = true;
		return false;
	}
	else {
		if (lastGrabState == true) {
			lastGrabState = false;
			return true;
		}
	}
}

bool GameTexture::grabbed()
{
	if (grab == false)
	{
		lastDropState = true;
		return false;
	}
	else {
		if (lastDropState == true) {
			lastDropState = false;
			setGrabPosition(getCurrentPosition());
			return true;
		}
	}
}

void GameTexture::setGrabPosition(SDL_Point position)
{
	grabPosition.x = position.x;
	grabPosition.y = position.y;
}

bool GameTexture::handleEvent(SDL_Event* event) {
	bool spritePressed = false;

	if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_Color color = {0, 0, 0, 0};
		SDL_GetMouseState(&x, &y);
		bool inside = true;

		if (x < destRect.x)
			inside = false;
		else if (x > destRect.x + width)
			inside = false;
		else if (y < destRect.y)
			inside = false;
		else if (y > destRect.y + height)
			inside = false;

		if (!inside)
		    currentSprite = MOUSE_OUT;
		//Mouse is inside area
		else
		{
			switch (event->type)
			{
			case SDL_MOUSEMOTION:
				color = getPixelColor(x - destRect.x, y - destRect.y);				
				if (color.a != 0)
					currentSprite = MOUSE_OVER_MOTION;
				else
					currentSprite = MOUSE_OUT;
				break;

			case SDL_MOUSEBUTTONDOWN:				
				color = getPixelColor(x-destRect.x, y-destRect.y);
				if (color.a != 0) // Grab sprite only where there is color (alpha != 0)
				{
					currentSprite = MOUSE_DOWN;
					spritePressed = true;
					grab = true;
				}
				break;

			case SDL_MOUSEBUTTONUP:
				currentSprite = MOUSE_UP;
				spritePressed = false;
				grab = false;
				break;
			}
		}
	}
	return spritePressed;
}

SDL_Color GameTexture::getPixelColor(const int X, const int Y)
{
	int Bpp = spriteSurface->format->BytesPerPixel;
	Uint8* pPixel = (Uint8*)spriteSurface->pixels + Y * spriteSurface->pitch + X * Bpp;

	Uint32 PixelColor = *(Uint32*)pPixel;

	SDL_Color Color = { 0, 0, 0, 0 };

	SDL_GetRGBA(PixelColor, spriteSurface->format, &Color.r, &Color.g, &Color.b, &Color.a);

	return Color;
}

