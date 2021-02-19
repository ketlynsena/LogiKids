#include "pch.h"
#include "../LogiKids/game.h"
#include "../LogiKids/game_texture.h"


TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(TestGameObject, TestGetXpos) {

	GameTexture* GameTest;

	GameTest = new GameTexture("../../LogiKids/assets/tela_principal.png", 0, 0, false, false);
	//GameTest = new GameObject("0", 0, 0);
	bool pressed = GameTest->isPressed();
	EXPECT_FALSE(pressed);
	//EXPECT_EQ(xpos, 0);
	//EXPECT_TRUE(true);
}

