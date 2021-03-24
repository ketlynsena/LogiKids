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

TEST(TestGame, TestMenuEvent)
{
	Game* game = new Game();
	MEvent event;
	event.type = SDL_KEYDOWN;

	game->handleMenuEvents(&event);
	EXPECT_EQ(game->state, GAME_LEVELS);
}

TEST(TestGame, TestStoryEvents)
{
	Game* game = new Game();
	game->init("LogiKids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	MEvent event;
	event.type = SDL_MOUSEBUTTONDOWN;
	event.x = 760; // X button placement
	event.y = 37;

	game->handleStoryEvents(&event);
	EXPECT_EQ(game->state, GAME_MENU);

	event.x = 743; // Play button placement
	event.y = 554;

	game->handleStoryEvents(&event);
	EXPECT_EQ(game->state, GAME_LEVELS);	
}

TEST(TestGame, TestLevelEvents)
{
	Game* game = new Game();
	game->init("LogiKids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	MEvent event;
	game->state = GAME_LEVELS;

	event.type = SDL_MOUSEBUTTONDOWN;
	event.x = 276; // Level marker 0  placement
	event.y = 535;
	game->handleLevelEvents(&event);
	EXPECT_EQ(game->state, GAME_QUEENS);

	event.x = 373+27; // Level marker 1  placement
	event.y = 504+27;
	game->handleLevelEvents(&event);
	EXPECT_EQ(game->state, GAME_MAP_COLORING);

	event.x = 368 + 27; // Level marker 2  placement
	event.y = 425 + 27;
	game->handleLevelEvents(&event);
	EXPECT_EQ(game->state, GAME_HANOI);

	event.x = 488 + 27; // Level marker 3  placement
	event.y = 447 + 27;
	game->handleLevelEvents(&event);
	EXPECT_EQ(game->state, GAME_KNAPSACK);

	event.x = 614 + 27; // Level marker 4  placement
	event.y = 472 + 27;
	game->handleLevelEvents(&event);
	EXPECT_EQ(game->state, GAME_SCALE);

	event.x = 687 + 27; // Level marker 5  placement
	event.y = 401 + 27;
	game->handleLevelEvents(&event);
	EXPECT_EQ(game->state, GAME_TSP);

	event.x = 760; // X button placement
	event.y = 37;
	game->handleLevelEvents(&event);
	EXPECT_EQ(game->state, GAME_MENU);
}

TEST(TestGame, TestNQueensEvents)
{
	Game* game = new Game();
	game->init("LogiKids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	game->timer->start();
	MEvent event;
	event.type = SDL_MOUSEBUTTONDOWN;
	event.x = 760; // X button placement
	event.y = 37;

	game->handleNQueensEvents(&event);
	EXPECT_EQ(game->state, GAME_LEVELS);
}

TEST(TestGame, TestMapColoringEvents)
{
	Game* game = new Game();
	game->init("LogiKids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	game->timer->start();
	MEvent event;
	event.type = SDL_MOUSEBUTTONDOWN;
	event.x = 760; // X button placement
	event.y = 37;

	game->handleMapColoringEvents(&event);
	EXPECT_EQ(game->state, GAME_LEVELS);
}

TEST(TestGame, TestHanoiEvents)
{
	Game* game = new Game();
	game->init("LogiKids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	game->timer->start();
	MEvent event;
	event.type = SDL_MOUSEBUTTONDOWN;
	event.x = 760; // X button placement
	event.y = 37;

	game->handleHanoiEvents(&event);
	EXPECT_EQ(game->state, GAME_LEVELS);
}

TEST(TestGame, TestKnapsackEvents)
{
	Game* game = new Game();
	game->init("LogiKids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	game->timer->start();
	MEvent event;
	event.type = SDL_MOUSEBUTTONDOWN;
	event.x = 760; // X button placement
	event.y = 37;

	game->handleKnapsackEvents(&event);
	EXPECT_EQ(game->state, GAME_LEVELS);
}

TEST(TestGame, TestScaleEvents)
{
	Game* game = new Game();
	game->init("LogiKids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	game->timer->start();
	MEvent event;
	event.type = SDL_MOUSEBUTTONDOWN;
	event.x = 760; // X button placement
	event.y = 37;

	game->handleScaleEvents(&event);
	EXPECT_EQ(game->state, GAME_LEVELS);
}

TEST(TestGame, TestTSPEvents)
{
	Game* game = new Game();
	game->init("LogiKids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	game->timer->start();
	MEvent event;
	event.type = SDL_MOUSEBUTTONDOWN;
	event.x = 760; // X button placement
	event.y = 37;

	game->handleTSPEvents(&event);
	EXPECT_EQ(game->state, GAME_LEVELS);
}

TEST(TestGame, TestHandleEvents)
{
	Game* game = new Game();
	game->init("LogiKids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	MEvent event;
	event.type = SDL_QUIT;
	event.x = 760; // X button placement
	event.y = 37;

	game->handleEvents(event);
	EXPECT_FALSE(game->running());

	event.type = SDL_MOUSEBUTTONDOWN;
	game->state = GAME_MENU;
	game->handleEvents(event);
	game->render();

	game->state = GAME_STORY;
	game->handleEvents(event);
	game->render();

	game->state = GAME_QUEENS;
	game->handleEvents(event);
	game->render();

	game->state = GAME_MAP_COLORING;
	game->handleEvents(event);
	game->render();

	game->state = GAME_HANOI;
	game->handleEvents(event);
	game->render();

	game->state = GAME_KNAPSACK;
	game->handleEvents(event);
	game->render();

	game->state = GAME_SCALE;
	game->handleEvents(event);
	game->render();

	game->state = GAME_TSP;
	game->handleEvents(event);
	game->render();

	game->state = GAME_LEVELS;
	game->handleEvents(event);
	game->render();

	EXPECT_FALSE(game->timer->isPaused());
}

TEST(TestGame, TestRender)
{
	Game* game = new Game();
	game->init("LogiKids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	MEvent event;
	event.type = SDL_QUIT;
	event.x = 760; // X button placement
	event.y = 37;

	game->state = GAME_MENU;
	game->render();

	game->state = GAME_STORY;
	game->render();

	game->state = GAME_LEVELS;
	game->render();

	game->state = GAME_QUEENS;
	game->render();

	game->state = GAME_MAP_COLORING;
	game->render();

	game->state = GAME_HANOI;
	game->render();

	game->state = GAME_KNAPSACK;
	game->render();

	game->state = GAME_SCALE;
	game->render();

	game->state = GAME_TSP;
	game->render();

	EXPECT_TRUE(game->running());
}

TEST(TestGame, TestClean)
{
	Game* game = new Game();
	game->init("LogiKids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	MEvent event;
	event.type = SDL_QUIT;

	game->handleEvents(event);
	EXPECT_FALSE(game->running());
	game->clean();
}

TEST(TestGame, TestTimerUpdate)
{
	Game* game = new Game();
	game->init("LogiKids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	game->timer->start();
	game->state = GAME_QUEENS;
	game->update();
	game->state = GAME_HANOI;
	game->update();
	game->state = GAME_KNAPSACK;
	game->update();
	game->state = GAME_SCALE;
	game->update();
	game->state = GAME_TSP;
	game->update();
	EXPECT_TRUE(game->timer->isStarted());
}

TEST(TestGame, TestPollEvent)
{
	Game* game = new Game();
	game->init("LogiKids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	game->pollEvent();
}
