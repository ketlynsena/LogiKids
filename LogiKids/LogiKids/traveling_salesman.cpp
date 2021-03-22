#include "traveling_salesman.h"
#include "game.h"

TravelingSalesman::TravelingSalesman()
{
	background = new GameTexture("assets/traveling_salesman/mineiro_viajante.png", 0, 0, false, false);
	help = new GameTexture("assets/buttons/help", 740, 540, true, false);
	reset = new GameTexture("assets/buttons/reset", 15, 540, true, false);
	distancesTexture = new GameTexture("assets/traveling_salesman/distancias.png", 420, 231, false, false);
	distance_text = new TextTexture("0", branco, Game::consolas, 30, 164, 428);

	loadCityPins();
	loadEdges();
}

void TravelingSalesman::loadCityPins()
{
	pin[0] = new GameTexture("assets/traveling_salesman/pin", 376, 360, true, false);
	pin[1] = new GameTexture("assets/traveling_salesman/pin", 455, 265, true, false);
	pin[2] = new GameTexture("assets/traveling_salesman/pin", 555, 197, true, false);
	pin[3] = new GameTexture("assets/traveling_salesman/pin", 656, 254, true, false);
	pin[4] = new GameTexture("assets/traveling_salesman/pin", 520, 344, true, false);
	pin[5] = new GameTexture("assets/traveling_salesman/pin", 717, 283, true, false);
	pin[6] = new GameTexture("assets/traveling_salesman/pin", 516, 419, true, false);
	pin[7] = new GameTexture("assets/traveling_salesman/pin", 577, 374, true, false);
	pin[8] = new GameTexture("assets/traveling_salesman/pin", 661, 348, true, false);
	pin[9] = new GameTexture("assets/traveling_salesman/pin", 505, 488, true, false);
	pin[10] = new GameTexture("assets/traveling_salesman/pin", 562, 451, true, false);
	pin[11] = new GameTexture("assets/traveling_salesman/pin", 619, 466, true, false);
}

void TravelingSalesman::loadEdges()
{
	
	map[0][1].texture = new GameTexture("assets/traveling_salesman/edges/0-1.png", 382, 277, false, false);	
	map[1][0].texture = new GameTexture("assets/traveling_salesman/edges/0-1.png", 382, 277, false, false);
	map[0][1].distance = 5;
	map[1][0].distance = 5;
		
	map[0][4].texture = new GameTexture("assets/traveling_salesman/edges/0-4.png", 383, 355, false, false);
	map[4][0].texture = new GameTexture("assets/traveling_salesman/edges/0-4.png", 383, 355, false, false);
	map[0][4].distance = 7;
	map[4][0].distance = 7;

	map[0][6].texture = new GameTexture("assets/traveling_salesman/edges/0-6.png", 383, 370, false, false);
	map[6][0].texture = new GameTexture("assets/traveling_salesman/edges/0-6.png", 383, 370, false, false);
	map[0][6].distance = 8;
	map[6][0].distance = 8;

	map[0][9].texture = new GameTexture("assets/traveling_salesman/edges/0-9.png", 382, 370, false, false);
	map[9][0].texture = new GameTexture("assets/traveling_salesman/edges/0-9.png", 382, 370, false, false);
	map[0][9].distance = 10;
	map[9][0].distance = 10;

	map[1][2].texture = new GameTexture("assets/traveling_salesman/edges/1-2.png", 462, 209, false, false);
	map[2][1].texture = new GameTexture("assets/traveling_salesman/edges/1-2.png", 462, 209, false, false);
	map[2][1].distance = 10;
	map[1][2].distance = 10;

	map[1][4].texture = new GameTexture("assets/traveling_salesman/edges/1-4.png", 462, 277, false, false);
	map[4][1].texture = new GameTexture("assets/traveling_salesman/edges/1-4.png", 462, 277, false, false);
	map[1][4].distance = 6;
	map[4][1].distance = 6;

	map[2][3].texture = new GameTexture("assets/traveling_salesman/edges/2-3.png", 562, 209, false, false);
	map[3][2].texture = new GameTexture("assets/traveling_salesman/edges/2-3.png", 562, 209, false, false);
	map[2][3].distance = 9;
	map[3][2].distance = 9;

	map[2][4].texture = new GameTexture("assets/traveling_salesman/edges/2-4.png", 527, 210, false, false);
	map[4][2].texture = new GameTexture("assets/traveling_salesman/edges/2-4.png", 527, 210, false, false);
	map[2][4].distance = 12;
	map[4][2].distance = 12;

	map[3][4].texture = new GameTexture("assets/traveling_salesman/edges/3-4.png", 527, 265, false, false);
	map[4][3].texture = new GameTexture("assets/traveling_salesman/edges/3-4.png", 527, 265, false, false);
	map[3][4].distance = 11;
	map[4][3].distance = 11;

	map[3][5].texture = new GameTexture("assets/traveling_salesman/edges/3-5.png", 664, 265, false, false);
	map[5][3].texture = new GameTexture("assets/traveling_salesman/edges/3-5.png", 664, 265, false, false);
	map[3][5].distance = 6;
	map[5][3].distance = 6;

	map[3][7].texture = new GameTexture("assets/traveling_salesman/edges/3-7.png", 584, 266, false, false);
	map[7][3].texture = new GameTexture("assets/traveling_salesman/edges/3-7.png", 584, 266, false, false);
	map[3][7].distance = 10;
	map[7][3].distance = 10;

	map[3][8].texture = new GameTexture("assets/traveling_salesman/edges/3-8.png", 663, 267, false, false);
	map[8][3].texture = new GameTexture("assets/traveling_salesman/edges/3-8.png", 663, 267, false, false);
	map[3][8].distance = 9;
	map[8][3].distance = 9;

	map[4][6].texture = new GameTexture("assets/traveling_salesman/edges/4-6.png", 523, 357, false, false);
	map[6][4].texture = new GameTexture("assets/traveling_salesman/edges/4-6.png", 523, 357, false, false);
	map[4][6].distance = 4;
	map[6][4].distance = 4;

	map[4][7].texture = new GameTexture("assets/traveling_salesman/edges/4-7.png", 528, 356, false, false);
	map[7][4].texture = new GameTexture("assets/traveling_salesman/edges/4-7.png", 528, 356, false, false);
	map[4][7].distance = 3;
	map[7][4].distance = 3;

	map[5][8].texture = new GameTexture("assets/traveling_salesman/edges/5-8.png", 668, 295, false, false);
	map[8][5].texture = new GameTexture("assets/traveling_salesman/edges/5-8.png", 668, 295, false, false);
	map[5][8].distance = 8;
	map[8][5].distance = 8;

	map[6][7].texture = new GameTexture("assets/traveling_salesman/edges/6-7.png", 523, 386, false, false);
	map[7][6].texture = new GameTexture("assets/traveling_salesman/edges/6-7.png", 523, 386, false, false);
	map[6][7].distance = 4;
	map[7][6].distance = 4;

	map[6][9].texture = new GameTexture("assets/traveling_salesman/edges/6-9.png", 509, 431, false, false);
	map[9][6].texture = new GameTexture("assets/traveling_salesman/edges/6-9.png", 509, 431, false, false);
	map[6][9].distance = 3;
	map[9][6].distance = 3;

	map[6][10].texture = new GameTexture("assets/traveling_salesman/edges/6-10.png", 523, 430, false, false);
	map[10][6].texture = new GameTexture("assets/traveling_salesman/edges/6-10.png", 523, 430, false, false);
	map[6][10].distance = 2;
	map[10][6].distance = 2;

	map[7][8].texture = new GameTexture("assets/traveling_salesman/edges/7-8.png", 585, 359, false, false);
	map[8][7].texture = new GameTexture("assets/traveling_salesman/edges/7-8.png", 585, 359, false, false);
	map[7][8].distance = 6;
	map[8][7].distance = 6;

	map[7][10].texture = new GameTexture("assets/traveling_salesman/edges/7-10.png", 569, 386, false, false);
	map[10][7].texture = new GameTexture("assets/traveling_salesman/edges/7-10.png", 569, 386, false, false);
	map[7][10].distance = 4;
	map[10][7].distance = 4;

	map[7][11].texture = new GameTexture("assets/traveling_salesman/edges/7-11.png", 584, 386, false, false);
	map[11][7].texture = new GameTexture("assets/traveling_salesman/edges/7-11.png", 584, 386, false, false);
	map[7][11].distance = 7;
	map[11][7].distance = 7;

	map[8][11].texture = new GameTexture("assets/traveling_salesman/edges/8-11.png", 626, 360, false, false);
	map[11][8].texture = new GameTexture("assets/traveling_salesman/edges/8-11.png", 626, 360, false, false);
	map[8][11].distance = 10;
	map[11][8].distance = 10;

	map[9][10].texture = new GameTexture("assets/traveling_salesman/edges/9-10.png", 510, 462, false, false);
	map[10][9].texture = new GameTexture("assets/traveling_salesman/edges/9-10.png", 510, 462, false, false);
	map[9][10].distance = 3;
	map[10][9].distance = 3;

	map[9][11].texture = new GameTexture("assets/traveling_salesman/edges/9-11.png", 511, 477, false, false);
	map[11][9].texture = new GameTexture("assets/traveling_salesman/edges/9-11.png", 511, 477, false, false);
	map[9][11].distance = 6;
	map[11][9].distance = 6;

	map[10][11].texture = new GameTexture("assets/traveling_salesman/edges/10-11.png", 570, 462, false, false);
	map[11][10].texture = new GameTexture("assets/traveling_salesman/edges/10-11.png", 570, 462, false, false);
	map[10][11].distance = 3;
	map[11][10].distance = 3;
}

void TravelingSalesman::render()
{
	background->render();
	help->render();
	reset->render();

	for (int i = 0; i < N_CITIES; i++)
	{
		for (int j = 0; j < N_CITIES; j++)
		{
			if (j < i)
			{
				if(map[i][j].texture && map[i][j].visible)
					map[i][j].texture->render();
			}
		}		
	}

	for (int i = 0; i < N_CITIES; i++)
	{
		pin[i]->render();
	}

	distancesTexture->render();
	distance_text->render();
	Game::renderGameScore();
}

void TravelingSalesman::update()
{
	if (checkWin())
	 {
		gameWin = true;
	}
}

void TravelingSalesman::handleEvent(SDL_Event* e)
{
	help->handleEvent(e);

	if (reset->handleEvent(e))
		resetLevel();

	handlePinEvents(e);
	
}

void TravelingSalesman::handlePinEvents(SDL_Event* e)
{
	int currentPin = getCurrentCity();
	//printf("Neighbours of %d: ", currentPin);
	for (int i = 0; i < N_CITIES; i++)
	{
		if (map[currentPin][i].texture || map[i][currCity].texture) // If current city shares an edge with another and was not connected
		{
			//printf("%d, ", i);
			if (pin[i]->handleEvent(e)) // Neighbour pin was pressed
			{
				if (cityNotVisited(i)) {
					addCityToPath(i);
					//printPath();
				}				
			}
		}
	}
	//printf("\n");
}

void TravelingSalesman::printPath()
{
	printf("Current path (%d visited):\n", n_cities_visited);
	for (int i = 0; i < N_CITIES; i++)
	{
		printf("[%d] ", path[i]);
	}
	printf("\n");
}

bool TravelingSalesman::cityNotVisited(int city)
{
	for (int i = 0; i < N_CITIES; i++)
	{
		if (path[i] == city)
			return false;
	}
	return true;
}

void TravelingSalesman::addCityToPath(int city)
{
	map[currCity][city].visible = true;
	map[city][currCity].visible = true;

	path_distance += map[currCity][city].distance;

	printf("Curr distance: %d\n", path_distance);
	distance_text->loadText(std::to_string(path_distance), branco, Game::consolas, 30);

	path[n_cities_visited] = city;
	n_cities_visited++;

	setCurrentCity(city);
}

int TravelingSalesman::getCurrentCity()
{
	return currCity;
}

void TravelingSalesman::setCurrentCity(int city)
{
	currCity = city;
}

void TravelingSalesman::resetLevel()
{
	gameWin = false;
	n_cities_visited = 0;
	currCity = START;
	path_distance = 0;

	for (int i = 0; i < N_CITIES; i++)
	{
		for (int j = 0; j < N_CITIES; j++)
		{
			map[i][j].visible = false;
			map[j][i].visible = false;
		}
		path[i] = -1; // Unvisited
	}
	distance_text->loadText(std::to_string(path_distance), branco, Game::consolas, 30);
}

void TravelingSalesman::recordMove(int i, int j, int last_city)
{
	lastMove.i = i;
	lastMove.j = j;
	lastMove.last_city = last_city;
}

bool TravelingSalesman::checkWin()
{
	if (n_cities_visited < 12)
		return false;

	if (path[N_CITIES-1] != START)
		return false;

	for (int i = 0; i < N_CITIES; i++)
	{
		if (path[i] != shortest_path[i])
			return false;
	}

	return true;
}

bool TravelingSalesman::gameWon()
{
	return gameWin;
}

TravelingSalesman::~TravelingSalesman()
{
}
