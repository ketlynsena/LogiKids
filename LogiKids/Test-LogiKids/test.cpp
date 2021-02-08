#include "pch.h"
#include "../LogiKids/game.h"
#include "../LogiKids/game_object.h"
#include "../LogiKids/texture_manager.h"
#include "../LogiKids/button.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(TestGameObject, TestGetXpos) {

	GameObject* GameTest;

	//GameTest = new GameObject("../../LogiKids/assets/tela_principal.png", 0, 0);
	//GameTest = new GameObject("0", 0, 0);
	//int xpos = GameTest->getXpos();
	EXPECT_EQ(xpos, 0);
	EXPECT_TRUE(true);
}

