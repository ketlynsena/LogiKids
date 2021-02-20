#include "pch.h"
#include "../LogiKids/game.h"
#include "../LogiKids/game_texture.h"


TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

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
