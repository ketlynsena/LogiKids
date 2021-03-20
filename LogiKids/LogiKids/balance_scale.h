#pragma once

#include "game_texture.h"
#include "text_texture.h"
#include <iostream>
#include <string>
#include <stdlib.h> 

#define N_WEIGHTS 8
#define MAX_WEIGHS 2

// Estados da balança
#define LEVEL 0
#define LEAN_RIGHT 1
#define LEAN_LEFT 2

class BalanceScale
{
public:
	BalanceScale();
	~BalanceScale();
	void render();
	void handleEvent(SDL_Event* e);
	void update();
	int getScaleState();
	void setScaleState(int state);
	void resetLevel();
	bool checkWin();
	bool gameWon();

private:
	GameTexture* background;
	GameTexture* help;
	GameTexture* reset;
	GameTexture* scale[3]; // A balança tem 3 estados
	GameTexture* weight[N_WEIGHTS];
	GameTexture* solution_area;
	GameTexture* weighs[MAX_WEIGHS+1]; // +1 para 0
	GameTexture* button;
	int scale_state = LEVEL;
	bool gameWin = false;
	int n_weighs = 0; // Pesagem inicial em 0

};

