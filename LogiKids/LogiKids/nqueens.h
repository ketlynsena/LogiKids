#pragma once
#include "texture_manager.h"
#include "game_object.h"
#include "game.h"
#include "button.h"
#include "sprite.h"
#include <iostream>
#include <string>

class N_Queens
{
public:
	N_Queens();
	~N_Queens();
	void handleEvent(SDL_Event* e);
	void update();
	void render();

private:
	bool board[4][4];
	GameObject* background;
	GameObject* board_texture;
	Sprite* queen;

};

