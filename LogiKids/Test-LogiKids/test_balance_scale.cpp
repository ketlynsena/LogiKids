#include "pch.h"
//#include "../LogiKids/game.h"
#include "../LogiKids/balance_scale.h"

TEST(TestBalanceScale, TestInit)
{
	BalanceScale* balanca = new BalanceScale();
	EXPECT_TRUE(balanca);
}

TEST(TestBalanceScale, TestWeigh)
{
	Index idx;
	idx.n = 0;
	idx.plate = LEFT_PLATE;

	BalanceScale* balanca = new BalanceScale();
	balanca->weigh();
	EXPECT_EQ(LEVEL, balanca->getScaleState());
	balanca->addWeightToScale(balanca->weight[1], idx, 1);
	balanca->weigh();
	EXPECT_EQ(LEAN_LEFT, balanca->getScaleState());

	idx.plate = RIGHT_PLATE;
	balanca->addWeightToScale(balanca->weight[2], idx, 2);

	idx.n = 1;
	balanca->addWeightToScale(balanca->weight[3], idx, 3);
	balanca->weigh();

	EXPECT_EQ(LEAN_RIGHT, balanca->getScaleState());
}

TEST(TestBalanceScale, TestGetPlateIndex)
{
	Index idx;
	idx.n = 0;
	idx.plate = LEFT_PLATE;

	BalanceScale* balanca = new BalanceScale();
	balanca->addWeightToScale(balanca->weight[1], idx, 1);

	EXPECT_EQ(idx.plate, balanca->getPlateIndex(balanca->weight[1]).plate);
	EXPECT_EQ(idx.n, balanca->getPlateIndex(balanca->weight[1]).n);
}

TEST(TestBalanceScale, TestAddWeightToSolutionArea)
{
	BalanceScale* balanca = new BalanceScale();
	balanca->addWeightToSolutionArea(balanca->weight[0]);

	SDL_Point areaPos = balanca->solution_area->getCurrentPosition();

	EXPECT_EQ(areaPos.x, balanca->weight[0]->getCurrentPosition().x);
	EXPECT_EQ(areaPos.y, balanca->weight[0]->getCurrentPosition().y);
}

TEST(TestBalanceScale, TestIfWithinSolutionArea)
{
	BalanceScale* balanca = new BalanceScale();
	EXPECT_FALSE(balanca->checkIfWithinSolutionArea(balanca->weight[0]));
}

TEST(TestBalanceScale, TestAddWeightToScale)
{
	Index idx;
	idx.n = 0;
	idx.plate = LEFT_PLATE;
	BalanceScale* balanca = new BalanceScale();
	EXPECT_TRUE(balanca->addWeightToScale(balanca->weight[0], idx, 0));
	EXPECT_TRUE(balanca->addWeightToScale(balanca->weight[1], idx, 1));
	EXPECT_TRUE(balanca->addWeightToScale(balanca->weight[2], idx, 2));
	EXPECT_TRUE(balanca->addWeightToScale(balanca->weight[3], idx, 3));
	EXPECT_FALSE(balanca->addWeightToScale(balanca->weight[4], idx, 4));
}

TEST(TestBalanceScale, TestRemoveWeightFromScale)
{
	Index idx;
	idx.n = 0;
	idx.plate = LEFT_PLATE;
	BalanceScale* balanca = new BalanceScale();

	balanca->addWeightToScale(balanca->weight[0], idx, 0);
	balanca->removeWeightFromScale(0);
	EXPECT_EQ(balanca->scale_plates[LEFT_PLATE][0], -1);

	idx.plate = RIGHT_PLATE;
	balanca->addWeightToScale(balanca->weight[0], idx, 0);
	balanca->removeWeightFromScale(0);
	EXPECT_EQ(balanca->scale_plates[RIGHT_PLATE][0], -1);
}

TEST(TestBalanceScale, TestGetScaleState)
{
	BalanceScale* balanca = new BalanceScale();
	EXPECT_EQ(LEVEL, balanca->getScaleState());
}

TEST(TestBalanceScale, TestSetScaleState)
{
	BalanceScale* balanca = new BalanceScale();
	EXPECT_EQ(LEVEL, balanca->getScaleState());
	balanca->setScaleState(LEAN_RIGHT);
	EXPECT_EQ(LEAN_RIGHT, balanca->getScaleState());
	balanca->setScaleState(LEAN_LEFT);
	EXPECT_EQ(LEAN_LEFT, balanca->getScaleState());
}

TEST(TestBalanceScale, TestResetLevel)
{
	BalanceScale* balanca = new BalanceScale();
	balanca->setScaleState(LEAN_RIGHT);
	balanca->resetLevel();
	EXPECT_EQ(LEVEL, balanca->getScaleState());
}

TEST(TestBalanceScale, TestCheckWin)
{
	BalanceScale* balanca = new BalanceScale();
	EXPECT_FALSE(balanca->checkWin(1));
	EXPECT_TRUE(balanca->checkWin(0));
}

TEST(TestBalanceScale, TestGameWon)
{
	BalanceScale* balanca = new BalanceScale();
	EXPECT_FALSE(balanca->gameWon());
}




