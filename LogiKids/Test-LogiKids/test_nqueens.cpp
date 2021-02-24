#include "pch.h"
#include "../LogiKids/game.h"
#include "../LogiKids/game_texture.h"

TEST(TestNQueens, TestInsideBoardIndex) {

	N_Queens* nrainhas;
	nrainhas = new N_Queens();

	GameTexture* queen = nrainhas->getQueen(1);
	bool inside = nrainhas->insideBoard(queen);
	
	EXPECT_EQ(inside, false);
}

TEST(TestNQueens, TestGetBoardIndex) {
}

TEST(TestNQueens, TestAddQueenToBoard) {
}

TEST(TestNQueens, TestRemoveQueenToBoard) {
}

TEST(TestNQueens, TestCheckConflict) {
}

TEST(TestNQueens, TestCheckWin) {
}

TEST(TestNQueens, TestResetBoard) {
}


