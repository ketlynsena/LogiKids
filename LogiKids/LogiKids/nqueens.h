#pragma once
#include "texture_manager.h"
#include "game_object.h"
#include "game.h"
#include "button.h"
#include "sprite.h"
#include <iostream>
#include <string>
#include <stdlib.h> 

typedef struct TilePosition{
	int i; // x
	int j; // y
};

typedef struct QueenPiece {
	TilePosition index;
	Sprite* piece;
};

class N_Queens
{
public:
	N_Queens();
	~N_Queens();
	bool addQueenToBoard(TilePosition index, Sprite* queenPiece);
	void removeQueenFromBoard(TilePosition index);
	void resetLevel();
	void resetBoard();
	bool checkWin();
	bool checkConflict(TilePosition* index_list);
	void handleQueenPieceEvent(SDL_Event* e, Sprite* queenPiece);
	void handleEvent(SDL_Event* e);
	void update();
	void render();
	bool insideBoard(Sprite* queenPiece); 
	TilePosition getBoardIndex(Sprite* queenPiece);
	bool getGameState();

private:
	bool board[4][4]; // TODO
	TilePosition currentIndex; // variavel auxiliar
	GameObject* background;
	GameObject* board_texture;
	Sprite* queens[4]; // TODO
	Button* help;
	Button* reset;
	bool gameWin = false;
};

