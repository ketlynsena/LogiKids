#include "pch.h"
//#include "../LogiKids/game.h"
#include "../LogiKids/nqueens.h"

TEST(TestNQueens, TestInsideBoardIndex) {

	N_Queens* nrainhas;
	nrainhas = new N_Queens();

	GameTexture* queen = nrainhas->getQueen(1);
	bool inside = nrainhas->insideBoard(queen);
	
	EXPECT_EQ(inside, false);
}

TEST(TestNQueens, TestAddQueenToBoard) {
	N_Queens* nrainhas = new N_Queens();
	GameTexture* queen = new GameTexture("assets/rainha.png", 70, 340, false, true);
	TilePosition idx;
	idx.i = 0;
	idx.j = 1;

	EXPECT_TRUE(nrainhas->addQueenToBoard(idx, queen));

	EXPECT_FALSE(nrainhas->addQueenToBoard(idx, queen));
}

TEST(TestNQueens, TestRemoveQueenFromBoard) {
	N_Queens* nrainhas = new N_Queens();
	TilePosition idx;
	idx.i = 0;
	idx.j = 0;

	nrainhas->addQueenToBoard(idx, nrainhas->queens[0]);
	EXPECT_TRUE(nrainhas->board[idx.i][idx.j]);
	nrainhas->removeQueenFromBoard(idx);
	EXPECT_FALSE(nrainhas->board[idx.i][idx.j]);
}

TEST(TestNQueens, TestResetBoard) {
	N_Queens* nrainhas = new N_Queens();
	TilePosition idx;
	idx.i = 0;
	idx.j = 0;

	nrainhas->addQueenToBoard(idx, nrainhas->queens[0]);
	nrainhas->resetBoard();
	EXPECT_FALSE(nrainhas->board[idx.i][idx.j]);
}

TEST(TestNQueens, TestResetLevel)
{
	N_Queens* nrainhas = new N_Queens();
	TilePosition idx;
	idx.i = 0;
	idx.j = 0;

	nrainhas->addQueenToBoard(idx, nrainhas->queens[0]);
	nrainhas->resetLevel();
	EXPECT_FALSE(nrainhas->board[idx.i][idx.j]);
	EXPECT_FALSE(nrainhas->gameWon());
}

TEST(TestNQueens, TestCheckWin)
{
	N_Queens* nrainhas = new N_Queens();
	TilePosition idx;
	idx.i = 0;
	idx.j = 1;

	nrainhas->addQueenToBoard(idx, nrainhas->queens[0]);

	idx.i = 1;
	idx.j = 3;

	nrainhas->addQueenToBoard(idx, nrainhas->queens[1]);

	idx.i = 0;
	idx.j = 2;

	nrainhas->addQueenToBoard(idx, nrainhas->queens[2]);

	idx.i = 3;
	idx.j = 2;

	nrainhas->addQueenToBoard(idx, nrainhas->queens[3]);

	EXPECT_FALSE(nrainhas->checkWin());
}

TEST(TestNQueens, TestCheckConflict)
{
	N_Queens* nrainhas = new N_Queens();
	TilePosition idx;
	TilePosition queen_index[BOARD_SIZE];
	idx.i = 0;
	idx.j = 1;

	nrainhas->addQueenToBoard(idx, nrainhas->queens[0]);

	idx.i = 1;
	idx.j = 3;

	nrainhas->addQueenToBoard(idx, nrainhas->queens[1]);

	EXPECT_TRUE(nrainhas->checkConflict(queen_index));
}



