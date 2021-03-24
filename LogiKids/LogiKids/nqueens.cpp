#include "nqueens.h"

N_Queens::N_Queens()
{
	background	  = new GameTexture("assets/fundo_nrainhas.png",   0,   0,   false, false);
	board_texture = new GameTexture("assets/tabuleiro.png",		 360, 150, false, false);
	queens[0]	  = new GameTexture("assets/rainha.png",		  70, 340, false, true);
	queens[1]	  = new GameTexture("assets/rainha.png",		 190, 340, false, true);
	queens[2]	  = new GameTexture("assets/rainha.png",		  70, 450, false, true);
	queens[3]	  = new GameTexture("assets/rainha.png",		 190, 450, false, true);

	queen_shadows[0] = new GameTexture("assets/rainha_sombra.png", 70, 340, false, false);
	queen_shadows[1] = new GameTexture("assets/rainha_sombra.png", 190, 340, false, false);
	queen_shadows[2] = new GameTexture("assets/rainha_sombra.png", 70, 450, false, false);
	queen_shadows[3] = new GameTexture("assets/rainha_sombra.png", 190, 450, false, false);

	help		  = new GameTexture("assets/buttons/help",		 740, 540,  true, false);
	reset		  = new GameTexture("assets/buttons/reset",		  15, 540,  true, false);
	tip			  = new GameTexture("assets/dica_nrainhas.png",   48, 72, false, false);
	play		  = new GameTexture("assets/buttons/play",		 670, 458, true, false);
}

N_Queens::~N_Queens()
{
}

bool N_Queens::addQueenToBoard(TilePosition index, GameTexture* queenPiece) {
	if (board[index.i][index.j] == false) // tile empty
	{
		board[index.i][index.j] = true;
		int x, y;
		SDL_Point currPos = board_texture->getCurrentPosition();

		x = currPos.x + index.i * (board_texture->getWidth() / BOARD_SIZE); 
		y = currPos.y + index.j * (board_texture->getHeight() / BOARD_SIZE);

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
	for (int i = 0; i < BOARD_SIZE; i++)
		queens[i]->resetPosition();

	resetBoard();
	gameWin = false;
}

void N_Queens::resetBoard()
{
	int i, j;

	for(i = 0; i < BOARD_SIZE; i++) 
		for (j = 0; j < BOARD_SIZE; j++)
			board[i][j] = false;
}

bool N_Queens::checkWin()
{
	int pieces = 0, line_count = 0, col_count = 0, diag_count = 0;
	TilePosition queen_index[BOARD_SIZE];

	for (int i = 0; i < BOARD_SIZE; i++) {
		line_count = 0;
		col_count = 0;
		for (int j = 0; j < BOARD_SIZE; j++)
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

	if (pieces == BOARD_SIZE) // If all queens are on board
	{
		return checkConflict(queen_index);
	}
		
	else 
		return false;
}

bool N_Queens::checkConflict(TilePosition* index_list)
{
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


void N_Queens::handleQueenPieceEvent(MEvent* e, GameTexture* queenPiece)//(SDL_Event* e, GameTexture* queenPiece)
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
		grab_pos = queenPiece->getGrabPosition();
		if (insideBoard(queenPiece)) {
			currentIndex = getBoardIndex(queenPiece);
			removeQueenFromBoard(currentIndex);
		}
	}
}

void N_Queens::handleEvent(MEvent* e)//(SDL_Event* e) 
{
	if (!gameWin) {
		if (!showTip) {
			for (int i = 0; i < BOARD_SIZE; i++)
				handleQueenPieceEvent(e, queens[i]);

			if (help->handleEvent(e)) {
				showTip = true;
			}

			if (reset->handleEvent(e))
				resetLevel();
		}
		if (play->handleEvent(e)) {
			showTip = false;
		}
	}
}

TilePosition N_Queens::getBoardIndex(GameTexture* queenPiece)
{	
	TilePosition index;
	SDL_Point boardPos = board_texture->getCurrentPosition();

	int boardH = board_texture->getHeight(), 
		boardW = board_texture->getWidth(),
	    queenCenterX = queenPiece->getCurrentPosition().x + (queenPiece->getWidth() / 2), 
	    queenCenterY = queenPiece->getCurrentPosition().y + (queenPiece->getHeight() / 2);

	index.i = (queenCenterX - boardPos.x) / (boardW / BOARD_SIZE); 
	index.j = (queenCenterY - boardPos.y) / (boardH / BOARD_SIZE); 

	return index;
}

GameTexture* N_Queens::getQueen(int id) {
	if (id >= 0 && id < BOARD_SIZE)
		return queens[id];
	return NULL;
}

bool N_Queens::gameWon()
{
	return gameWin;
}

bool N_Queens::insideBoard(GameTexture* queenPiece)
{
	int queenCenterX = queenPiece->getCurrentPosition().x + (queenPiece->getWidth() / 2), 
		queenCenterY = queenPiece->getCurrentPosition().y + (queenPiece->getHeight() / 2),
		boardH = board_texture->getHeight(), 
		boardW = board_texture->getWidth();

	SDL_Point boardPos = board_texture->getCurrentPosition();

	if ((queenCenterX >= boardPos.x && queenCenterX < (boardPos.x + boardW)) &&
		(queenCenterY >= boardPos.y && queenCenterY < (boardPos.y + boardH)))
	{
		return true;
	}

	return false;
}

void N_Queens::update() 
{
	if (checkWin()) 
		gameWin = true;
	else // Only move queens if game is not won  
		for (int i = 0; i < BOARD_SIZE; i++)
			queens[i]->updatePosFromMouseState();
}

void N_Queens::render() 
{
	background	 ->render();
	board_texture->render();
	help		 ->render();
	reset		 ->render();

	for (int i = 0; i < BOARD_SIZE; i++) {
		queen_shadows[i]->render();
		queens[i]->render();		
	}
	Game::renderGameScore();

	if (showTip) {
		tip->render();
		play->render();
	}
		

	// Render grabbed queen on top
	for (int i = 0; i < BOARD_SIZE; i++)
		if (queens[i]->isGrabbed())
			queens[i]->render();
}