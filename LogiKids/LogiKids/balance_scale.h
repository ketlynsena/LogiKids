#pragma once

#include "game_texture.h"
#include "text_texture.h"
#include <iostream>
#include <string>
#include <stdlib.h> 

#define N_WEIGHTS 8
#define MAX_WEIGHS 2

#define LEFT_PLATE 0
#define RIGHT_PLATE 1

// Estados da balança
#define LEVEL 0
#define LEAN_RIGHT 1
#define LEAN_LEFT -1

#define PLATE_WIDTH 136
#define PLATE_HEIGHT 50

#define LEFT_PLATE_X 206
#define RIGHT_PLATE_X 460

#define LEVEL_PLATE_Y 320
#define UP_PLATE_Y 288
#define DOWN_PLATE_Y 355

#define MAX_WEIGHS_ON_PLATE 4

typedef struct Index {
	int n; // x
	int plate; // y
};

class BalanceScale
{
public:
	BalanceScale();
	~BalanceScale();
	void renderScale();
	void render();
	void weigh();
	void handleEvent(MEvent* e); //(SDL_Event* e);
	void update();
	void addWeightToSolutionArea(GameTexture* w);
	bool checkIfWithinSolutionArea(GameTexture* w);
	void updateWeights();
	void removeWeightFromScale(int i);
	bool addWeightToScale(GameTexture* w, Index idx, int weight_number);
	int getScaleState();
	void setScaleState(int state);
	void resetLevel();
	bool checkWin(int i);
	bool gameWon();
	Index getPlateIndex(GameTexture* w);


	GameTexture* background;
	GameTexture* help;
	GameTexture* reset;
	GameTexture* scale_level; // A balança tem 3 estados
	GameTexture* scale_right;
	GameTexture* scale_left;
	GameTexture* weight[N_WEIGHTS];
	GameTexture* solution_area;
	GameTexture* weighs[MAX_WEIGHS+1]; // +1 para 0
	GameTexture* button;
	GameTexture* tip;
	GameTexture* play;
	bool showTip = false;
	Index index; // Auxiliary 
	int scale_plates[2][MAX_WEIGHS_ON_PLATE] = {{-1, -1, -1, -1},
												{-1, -1, -1, -1}};
	int scale_state = LEVEL;
	bool gameWin = false;
	bool wrong_answer = false;
	int n_weighs = 0; // Pesagem inicial em 0
private:
	int lighter_weight = 0;
};

