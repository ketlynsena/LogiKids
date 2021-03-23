#include "pch.h"
#include "../LogiKids/traveling_salesman.h"

TEST(TestTravelingSalesman, TestInit)
{
	TravelingSalesman* mineiro_viajante = new TravelingSalesman();
	EXPECT_TRUE(mineiro_viajante);
}

TEST(TestTravelingSalesman, TestRender)
{
	TravelingSalesman* mineiro_viajante = new TravelingSalesman();
	mineiro_viajante->render();
}

TEST(TestTravelingSalesman, TestHandleEvent)
{
	TravelingSalesman* mineiro_viajante = new TravelingSalesman();
	SDL_Event* e;
	mineiro_viajante->handleEvent(e);
}

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
	EXPECT_FALSE(mineiro_viajante->cityNotVisited(0));
}


