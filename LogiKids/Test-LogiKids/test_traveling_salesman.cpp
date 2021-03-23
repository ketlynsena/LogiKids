#include "pch.h"
#include "../LogiKids/traveling_salesman.h"

TEST(TestTravelingSalesman, TestInit)
{
	TravelingSalesman* mineiro_viajante = new TravelingSalesman();
	EXPECT_TRUE(mineiro_viajante);
}

/*TEST(TestTravelingSalesman, TestRender)
{
	TravelingSalesman* mineiro_viajante = new TravelingSalesman();
	mineiro_viajante->render();
	EXPECT_FALSE(mineiro_viajante->gameWon());
}*/

/*TEST(TestTravelingSalesman, TestHandleEvent)
{
	TravelingSalesman* mineiro_viajante = new TravelingSalesman();
	SDL_Event* e;
	mineiro_viajante->handleEvent(e);
	EXPECT_FALSE(mineiro_viajante->gameWon());
}*/

TEST(TestTravelingSalesman, TestUpdate)
{
	TravelingSalesman* mineiro_viajante = new TravelingSalesman();
	mineiro_viajante->update();
	EXPECT_FALSE(mineiro_viajante->gameWon());
}

TEST(TestTravelingSalesman, TestPrintPath)
{
	TravelingSalesman* mineiro_viajante = new TravelingSalesman();
	mineiro_viajante->printPath();
}

TEST(TestTravelingSalesman, TestCityNotVisited)
{
	TravelingSalesman* mineiro_viajante = new TravelingSalesman();
	EXPECT_TRUE(mineiro_viajante->cityNotVisited(0));
}

TEST(TestTravelingSalesman, TestAddCityToPath)
{
	TravelingSalesman* mineiro_viajante = new TravelingSalesman();
	mineiro_viajante->addCityToPath(0);
	EXPECT_FALSE(mineiro_viajante->cityNotVisited(0));
}

TEST(TestTravelingSalesman, TestGetCurrentCity)
{
	TravelingSalesman* mineiro_viajante = new TravelingSalesman();
	EXPECT_EQ(START, mineiro_viajante->getCurrentCity());
}

TEST(TestTravelingSalesman, TestSetCurrentCity)
{
	TravelingSalesman* mineiro_viajante = new TravelingSalesman();
	EXPECT_EQ(START, mineiro_viajante->getCurrentCity());
	mineiro_viajante->setCurrentCity(0);
	EXPECT_EQ(0, mineiro_viajante->getCurrentCity());
}

TEST(TestTravelingSalesman, TestResetLevel)
{
	TravelingSalesman* mineiro_viajante = new TravelingSalesman();
	mineiro_viajante->setCurrentCity(0);
	mineiro_viajante->resetLevel();
	EXPECT_EQ(START, mineiro_viajante->getCurrentCity());
}

TEST(TestTravelingSalesman, TestCheckWin)
{
	TravelingSalesman* mineiro_viajante = new TravelingSalesman();
	EXPECT_FALSE(mineiro_viajante->checkWin());
}

TEST(TestTravelingSalesman, TestGameWon)
{
	TravelingSalesman* mineiro_viajante = new TravelingSalesman();
	EXPECT_FALSE(mineiro_viajante->gameWon());
}

