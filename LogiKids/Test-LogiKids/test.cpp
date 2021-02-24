#include "pch.h"
#include "../LogiKids/game.h"
#include "../LogiKids/game_texture.h"

//Game Texture

TEST(TestGameTexture, TestInitPosition) {

	GameTexture* GameTest;
	SDL_Point originalPosition;
	int xpos = 0;
	int ypos = 0;

	GameTest = new GameTexture("a", xpos, ypos, false, false);
	originalPosition = GameTest->getOriginalPosition();
	EXPECT_EQ(xpos, originalPosition.x);
	EXPECT_EQ(ypos, originalPosition.y);

}

TEST(TestGameTexture, TestUpdatePosition) {

	GameTexture* GameTest;
	SDL_Point currentPosition;
	int xpos = 2;
	int ypos = 2;

	GameTest = new GameTexture("a", 0, 0, false, false);
	GameTest->setPosition(xpos, ypos);
	currentPosition = GameTest->getCurrentPosition();
	EXPECT_EQ(xpos, currentPosition.x);
	EXPECT_EQ(ypos, currentPosition.y);

}

TEST(TestGameTexture, TestResetPosition) {

	GameTexture* GameTest;
	SDL_Point currentPosition;
	int xpos = 2;
	int ypos = 2;

	GameTest = new GameTexture("a", xpos, ypos, false, false);
	GameTest->setPosition(0, 0);
	GameTest->resetPosition();
	currentPosition = GameTest->getCurrentPosition();
	EXPECT_EQ(xpos, currentPosition.x);
	EXPECT_EQ(ypos, currentPosition.y);

}

TEST(TestGameTexture, TestLoadTexture) {

	GameTexture* GameTest;
	SDL_Texture* Texture;
	
	GameTest = new GameTexture("assets/cursors/seta.png", 0, 0, false, false);
	Texture = GameTest->loadTexture("assets/cursors/seta.png");
	int w = GameTest->getWidth();
	printf("Width: %d\n", w);

	EXPECT_EQ(true, false);

}

//N-Queens

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


