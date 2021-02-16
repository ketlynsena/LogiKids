#pragma once

#include "game_texture.h"
#include "game.h"
#include <iostream>
#include <string>
#include <stdlib.h> 

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
	bool getGameState();

private:
	bool board[4][4]; // TODO
	TilePosition currentIndex; // variavel auxiliar
	GameTexture* background;
	GameTexture* board_texture;
	GameTexture* queens[4]; // TODO
	GameTexture* help;
	GameTexture* reset;
	bool gameWin = false;
};

