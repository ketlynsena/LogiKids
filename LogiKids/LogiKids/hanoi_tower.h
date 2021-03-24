#pragma once
#include "game_texture.h"
//#include "game.h"
#include <iostream>
#include <string>
#include <stdlib.h> 

#define N_LAYERS 4
#define N_TOWERS 3
#define TOWER_WIDTH 712
#define TOWER_HEIGHT 240
#define TOWER_X 44
#define TOWER_Y 276

typedef struct TowerIndex {
	int n_tower; // x
	int layer; // y
};

class Hanoi_Tower
{
public:
	Hanoi_Tower();
	~Hanoi_Tower();
	void render();
	void handleEvent(MEvent* e);// (SDL_Event* e);
	void resetLevel();
	void update();
	TowerIndex getTowerIndex(GameTexture* layer);
	bool placeLayeronTower(GameTexture* layer, int layerSize, TowerIndex index);
	bool noLayerOnTop(TowerIndex index);
	void printTower();
	bool layerBelowIsLarger(int layerSize, TowerIndex index);
	void updateLayers();
	bool gameWon();
	bool checkWin();

//private:
	GameTexture* background;
	GameTexture* help;
	GameTexture* reset;
	GameTexture* cake_layer[N_LAYERS];
	GameTexture* candle[N_TOWERS];
	int tower[N_LAYERS][N_TOWERS] = { {1,0,0}, {2,0,0}, {3,0,0}, {4,0,0} };
	TowerIndex currentIndex;
	TowerIndex grabIndex; // index on Tower where the layer was grabbed before being dropped
	bool freeLayer = false;
	bool gameWin = false;
	GameTexture* tip;
	GameTexture* play;
	bool showTip = false;
};

