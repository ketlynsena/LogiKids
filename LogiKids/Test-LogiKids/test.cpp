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


	//GameTest->setPosition(xpos, ypos);
	//currentPosition = GameTest->getCurrentPosition();

	//int xpos = GameTest->getXpos();
	//EXPECT_EQ(xpos, 0);
	//EXPECT_TRUE(true);
}

TEST(TestGameTexture, TestUpdatePosition) {
	GameTexture* GameTest;
	SDL_Point originalPosition;
	int xpos = 0;
	int ypos = 0;

	GameTest = new GameTexture("a", xpos, ypos, false, false);
	originalPosition = GameTest->getOriginalPosition();
	EXPECT_EQ(xpos, originalPosition.x);
	EXPECT_EQ(ypos, originalPosition.y);

}

TEST(TestGameTexture, TestResetPosition) {
}
