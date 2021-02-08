#include "nqueens.h"

N_Queens::N_Queens()
{
	background = new GameObject("assets/fundo_nrainhas.png", 0, 0);
	board_texture = new GameObject("assets/tabuleiro.png", 360, 150);
	queen = new Sprite("assets/rainha.png", 360, 150);
	queens[0] = new Sprite("assets/rainha.png", 50, 350);
	queens[1] = new Sprite("assets/rainha.png", 170, 350);
}

N_Queens::~N_Queens()
{
}

bool N_Queens::addQueenToBoard(TilePosition index, Sprite* queenPiece) {
	if (board[index.i][index.j] == false) // tile empty
	{
		board[index.i][index.j] = true;
		int x, y;

		x = board_texture->getXpos() + index.i * (board_texture->getWidth()/4); // TODO - hardcoded
		y = board_texture->getYpos() + index.j * (board_texture->getHeight() / 4);

		queenPiece->setPosition(x, y);
		return true;
	}
	return false;
}

void N_Queens::handleQueenPieceEvent(SDL_Event* e, Sprite* queenPiece)
{
	queenPiece->handleEvent(e);
	if (queenPiece->dropped())
	{
		printf("Dropped queen\n");
		if (insideBoard(queenPiece))
		{
			printf("Queen inside board\n");
			currentIndex = getBoardIndex(queenPiece);
			printf("Current index: %d,%d\n", currentIndex.i, currentIndex.j);
			if (addQueenToBoard(currentIndex, queenPiece))
			{
				printf("Added queen to board\n");
			}
			else {
				printf("Could not add queen to tile\n");
				queenPiece->resetPosition();
			}
		}
		else {
			printf("Queen outside\n");
			queenPiece->resetPosition();
		}
	}
}

void N_Queens::handleEvent(SDL_Event* e) 
{
	handleQueenPieceEvent(e, queen);
	handleQueenPieceEvent(e, queens[0]);
	handleQueenPieceEvent(e, queens[1]);
}

TilePosition N_Queens::getBoardIndex(Sprite* queenPiece)
{	
	TilePosition index;
	int boardX, boardY, boardH, boardW;
	int queenCenterX, queenCenterY;

	queenCenterX = queenPiece->getCurrentPosition().x + (queenPiece->getWidth() / 2);
	queenCenterY = queenPiece->getCurrentPosition().y + (queenPiece->getHeight() / 2);	

	boardX = board_texture->getXpos();
	boardY = board_texture->getYpos();

	boardH = board_texture->getHeight();
	boardW = board_texture->getWidth();

	index.i = (queenCenterX - boardX) / (boardW/4); // TODO - tirar hardcoded board size
	index.j = (queenCenterY - boardY) / (boardH / 4); // TODO

	return index;
}

bool N_Queens::insideBoard(Sprite* queenPiece)
{
	int queenCenterX, queenCenterY;
	queenCenterX = queenPiece->getCurrentPosition().x + (queenPiece->getWidth() / 2);
	queenCenterY = queenPiece->getCurrentPosition().y + (queenPiece->getHeight() / 2);

	int boardX, boardY, boardH, boardW;

	boardX = board_texture->getXpos();
	boardY = board_texture->getYpos();

	boardH = board_texture->getHeight();
	boardW = board_texture->getWidth();

	if ((queenCenterX >= boardX && queenCenterX < (boardX + boardW)) &&
		(queenCenterY >= boardY && queenCenterY < (boardY + boardH)))
	{
		return true;
	}

	return false;

}

void N_Queens::update() 
{
	queen->update();
	queens[0]->update();
	queens[1]->update();
}

void N_Queens::render() 
{
	background->render();
	board_texture->render();
	//queen->render();
	queens[0]->render();
	queens[1]->render();
}