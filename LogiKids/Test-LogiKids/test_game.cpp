#include "pch.h"
#include "../LogiKids/game.h"

TEST(TestGame, TestInit)
{
	Game* game = new Game();
	EXPECT_TRUE(game);
	game->init("LogiKids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	EXPECT_EQ(GAME_MENU, game->state);
	EXPECT_TRUE(game->running());
}

