#pragma once
#include "game_texture.h"
#include "text_texture.h"
#include <iostream>
#include <string>
#include <stdlib.h> 
//#include <format.h>

#define N_ITEMS 5 // Numero de items
#define KNAPSACK_LIMIT 15 // Peso limite da mochila
#define CADERNO 0 
#define LAPIS 1
#define MARCA_TEXTO 2
#define REGUA 3
#define TESOURA 4

typedef struct Item {
	GameTexture* itemTexture;
	int weight = 0;
	int value = 0;
	bool inside = false;
};


class Knapsack
{
public:
	Knapsack();
	~Knapsack();
	void render();
	void handleEvent(SDL_Event* e);
	void update();
	void updateItems();
	void resetLevel();
	bool checkWin();
	bool gameWon();
	bool packItem(Item* item);
	bool unpackItem(Item* item);
	void createItem(Item* item, const char* textureFile, int x, int y, int weight, int value);

private:
	GameTexture* background;
	GameTexture* help;
	GameTexture* reset;
	GameTexture* knapsack;
	TextTexture* maxW;
	TextTexture* currW;
	TextTexture* totVal;
	SDL_Color branco = { 255, 255, 255 };
	Item knapsackItem[N_ITEMS];
	GameTexture* itemShadow[N_ITEMS];
	int maxWeight = KNAPSACK_LIMIT;
	int currWeight = 0;
	int totValue = 0;
	bool gameWin = false;

};

