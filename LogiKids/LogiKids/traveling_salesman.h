#pragma once
#include "game_texture.h"
#include "text_texture.h"
#include <iostream>
#include <string>
#include <stdlib.h> 

#define N_CITIES 12
#define N_EDGES 25
#define START 7

typedef struct Edge {
	int distance; 
	bool visible = false;
	GameTexture* texture; 
};

typedef struct Move {
	int i;
	int j;
	int last_city;
};

class TravelingSalesman
{
public:
	TravelingSalesman();
	~TravelingSalesman();
	void render();
	void update();
	void handleEvent(MEvent* e);//(SDL_Event* e);
	void resetLevel();
	bool checkWin();
	bool gameWon();
	void loadCityPins();
	void loadEdges();
	void handlePinEvents(MEvent* e);//(SDL_Event* e);
	void addCityToPath(int city);
	void setCurrentCity(int city);
	int getCurrentCity();
	bool cityNotVisited(int city);
	void printPath();

private:
	GameTexture* background;
	GameTexture* help;
	GameTexture* reset;
	GameTexture* distancesTexture;

	GameTexture* pin[N_CITIES];
	TextTexture* distance_text;
	SDL_Color branco = { 255, 255, 255 };
	GameTexture* tip;
	GameTexture* play;
	bool showTip = false;
	bool gameWin = false;
	Edge map[N_CITIES][N_CITIES];
	Move lastMove;
	int path[N_CITIES] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};  
	int shortest_path[N_CITIES] = { 4, 6, 10, 9, 0, 1, 2, 3, 5, 8, 11, START };
	int currCity = START;
	int n_cities_visited = 0;
	int path_distance = 0;
};
