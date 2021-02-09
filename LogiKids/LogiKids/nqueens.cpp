#include "nqueens.h"

N_Queens::N_Queens()
{
	background	  = new GameObject("assets/fundo_nrainhas.png", 0, 0);
	board_texture = new GameObject("assets/tabuleiro.png", 360, 150);
	queens[0]	  = new Sprite("assets/rainha.png", 70, 340);
	queens[1]	  = new Sprite("assets/rainha.png", 190, 340);
	queens[2]	  = new Sprite("assets/rainha.png", 70, 450);
	queens[3]	  = new Sprite("assets/rainha.png", 190, 450);
	help		  = new Button("help", 740, 540);
	reset		  = new Button("reset", 15, 550);
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

void N_Queens::removeQueenFromBoard(TilePosition index)
{
	board[index.i][index.j] = false;
}

void N_Queens::resetLevel()
{
	queens[0]->resetPosition();
	queens[1]->resetPosition();
	queens[2]->resetPosition();
	queens[3]->resetPosition();

	resetBoard();

	gameWin = false;
}

void N_Queens::resetBoard()
{
	int i, j;

	for(i = 0; i < 4; i++) // TODO - remover hardcoded board size
		for (j = 0; j < 4; j++)
			board[i][j] = false;
}

bool N_Queens::checkWin()
{
	int pieces = 0, line_count = 0, col_count = 0, diag_count = 0;
	TilePosition queen_index[4];

	for (int i = 0; i < 4; i++) {
		line_count = 0;
		col_count = 0;
		for (int j = 0; j < 4; j++)
		{
			if (board[i][j]) { // scan by lines
				queen_index[pieces].i = i;
				queen_index[pieces].j = j;
				line_count++;
				pieces++;
				
			}
			if (board[j][i]) //scan by columns
				col_count++;
		}
		if (col_count > 1 || line_count > 1) // if queens attack each other
			return false;
	}

	/*for (int k = 0; k < 4 * 2; k++) {
		diag_count = 0;
		for (int j = 0; j <= k; j++) {
			int i = k - j;
			if (i < 4 && j < 4) {
				if (board[i][j]) {
					diag_count++;
				}					
			}
		}
		if (diag_count > 1)
			return false;
	}*/

	
	if (pieces == 4) // TODO - if all queens are on board
	{
		return checkConflict(queen_index);
	}
		
	else 
		return false;
}

bool N_Queens::checkConflict(TilePosition* index_list)
{
	/*
	printf("Reverse diagonal:\n");

	int maxSum = 4 + 4 - 2;

	for (int sum = 0; sum <= maxSum; sum++) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (i + j - sum == 0) {
					printf("%d ", board[i][j]);
				}
			}
		}
		printf("\n");
	}
	printf("\n");
	*/

	// Test for slash diagonal
	if ((board[1][0] + board[0][1] < 2) &&
		(board[2][0] + board[1][1] + board[0][2] < 2) &&
		(board[3][0] + board[2][1] + board[1][2] + board[0][3] < 2) &&
		(board[3][1] + board[2][2] + board[1][3] < 2) &&
		(board[3][2] + board[2][3] < 2) &&
		// Test for backslash diagonal
		(board[2][0] + board[3][1] < 2) &&
		(board[1][0] + board[2][1] + board[3][2] < 2) &&
		(board[0][0] + board[0][1] + board[2][2] + board[3][3] < 2) &&
		(board[0][1] + board[1][2] + board[2][3] < 2) &&
		(board[0][2] + board[1][3] < 2)
		) return true;
	else
		return false;
}


void N_Queens::handleQueenPieceEvent(SDL_Event* e, Sprite* queenPiece)
{
	queenPiece->handleEvent(e);
	if (queenPiece->dropped())
	{
		//printf("Dropped queen\n");
		if (insideBoard(queenPiece))
		{
			//printf("Queen inside board\n");
			currentIndex = getBoardIndex(queenPiece);
			//printf("Current index: %d,%d\n", currentIndex.i, currentIndex.j);
			if (!addQueenToBoard(currentIndex, queenPiece))
			{
				queenPiece->resetPosition();
			}
		}
		else {
			//printf("Queen outside\n");
			queenPiece->resetPosition();
		}
	}
	if (queenPiece->grabbed()) {
		SDL_Point grab_pos;
		//printf("Queen was grabbed at: ");
		grab_pos = queenPiece->getGrabPosition();
		//printf("%d, %d\n", grab_pos.x, grab_pos.y);
		if (insideBoard(queenPiece)) {
			//printf("Queen grabbed from board ");
			currentIndex = getBoardIndex(queenPiece);
			//printf("at index: %d,%d\n", currentIndex.i, currentIndex.j);
			removeQueenFromBoard(currentIndex);
		}
	}
}

void N_Queens::handleEvent(SDL_Event* e) 
{
	if (!gameWin) {
		handleQueenPieceEvent(e, queens[0]);
		handleQueenPieceEvent(e, queens[1]);
		handleQueenPieceEvent(e, queens[2]);
		handleQueenPieceEvent(e, queens[3]);

		help->handleEvent(e);

		if (reset->handleEvent(e)) {
			resetLevel();
		}
	}
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

bool N_Queens::getGameState()
{
	return gameWin;
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
	if (checkWin()) {
		gameWin = true;
	}
	else // Only move queens if game is not won 
	{ 
		queens[0]->update();
		queens[1]->update();
		queens[2]->update();
		queens[3]->update();
	}	
}

void N_Queens::render() 
{
	background->render();
	board_texture->render();
	help->render();
	reset->render();
	queens[0]->render();
	queens[1]->render();
	queens[2]->render();
	queens[3]->render();
}