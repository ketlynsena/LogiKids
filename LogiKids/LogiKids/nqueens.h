#pragma once

#include "game_texture.h"
#include "game.h"
#include <iostream>
#include <string>
#include <stdlib.h> 

#define BOARD_SIZE 4

typedef struct TilePosition{
	int i; // x
	int j; // y
};

typedef struct QueenPiece {
	TilePosition index;
	GameTexture* piece;
};

class N_Queens
{
public:
	N_Queens();
	~N_Queens();
	bool addQueenToBoard(TilePosition index, GameTexture* queenPiece);
	void removeQueenFromBoard(TilePosition index);
	void resetLevel();
	void resetBoard();
	bool checkWin();
	bool checkConflict(TilePosition* index_list);
	void handleQueenPieceEvent(SDL_Event* e, GameTexture* queenPiece);
	void handleEvent(SDL_Event* e);
	void update();
	void render();
	bool insideBoard(GameTexture* queenPiece); 
	TilePosition getBoardIndex(GameTexture* queenPiece);
	GameTexture* getQueen(int id);
	bool gameWon();

private:
	bool board[BOARD_SIZE][BOARD_SIZE] = { {0, 0, 0, 0},
										   {0, 0, 0, 0},
										   {0, 0, 0, 0},
										   {0, 0, 0, 0} };
	TilePosition currentIndex; // variavel auxiliar
	GameTexture* background;
	GameTexture* board_texture;
	GameTexture* queens[BOARD_SIZE];
	GameTexture* queen_shadows[BOARD_SIZE];
	GameTexture* help;
	GameTexture* reset;
	bool gameWin = false;
};

