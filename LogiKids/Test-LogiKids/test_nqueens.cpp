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
	N_Queens* nrainhas = new N_Queens();
	GameTexture* queen = new GameTexture("assets/rainha.png", 70, 340, false, true);
	TilePosition idx;
	idx.i = 0;
	idx.j = 1;

	EXPECT_TRUE(nrainhas->addQueenToBoard(idx, queen));

	EXPECT_FALSE(nrainhas->addQueenToBoard(idx, queen));
}

TEST(TestNQueens, TestRemoveQueenFromBoard) {
}

TEST(TestNQueens, TestCheckConflict) {
}

TEST(TestNQueens, TestCheckWin) {
}

TEST(TestNQueens, TestResetBoard) {
}


