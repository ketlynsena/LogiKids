#include "knapsack.h"
#include "game.h"

Knapsack::Knapsack()
{
	background = new GameTexture("assets/knapsack/problema_mochila.png", 0, 0, false, false);
	help = new GameTexture("assets/buttons/help", 740, 540, true, false);
	reset = new GameTexture("assets/buttons/reset", 15, 540, true, false);
	knapsack = new GameTexture("assets/buttons/mochila", 196, 318, true, false);

	createItem(&knapsackItem[CADERNO], "assets/knapsack/caderno.png", 450, 360, 12, 2);
	createItem(&knapsackItem[LAPIS], "assets/knapsack/lapis.png", 656, 167, 1, 2);
	createItem(&knapsackItem[MARCA_TEXTO], "assets/knapsack/marca_texto.png", 668, 409, 1, 1);
	createItem(&knapsackItem[REGUA], "assets/knapsack/regua.png", 445, 118, 10, 4);
	createItem(&knapsackItem[TESOURA], "assets/knapsack/tesoura.png", 558, 266, 4, 10);

	itemShadow[CADERNO] = new GameTexture("assets/knapsack/caderno_sombra.png", 451, 361, false, false);
	itemShadow[LAPIS] = new GameTexture("assets/knapsack/lapis_sombra.png", 657, 168, false, false);
	itemShadow[MARCA_TEXTO] = new GameTexture("assets/knapsack/marca_texto_sombra.png", 672, 412, false, false);
	itemShadow[REGUA] = new GameTexture("assets/knapsack/regua_sombra.png", 446, 119, false, false);
	itemShadow[TESOURA] = new GameTexture("assets/knapsack/tesoura_sombra.png", 559, 267, false, false);

	maxW = new TextTexture("15", branco, Game::consolas, 30, 80, 343);
	currW = new TextTexture("0", branco, Game::consolas, 30, 80, 418);
	totVal = new TextTexture("0", branco, Game::consolas, 30, 80, 494);
}

void Knapsack::createItem(Item* item, const char* textureFile, int x, int y, int weight, int value)
{
	item->itemTexture = new GameTexture(textureFile, x, y, false, true);
	item->inside = false;
	item->value = value;
	item->weight = weight;
}

Knapsack::~Knapsack()
{
}

void Knapsack::render()
{
	background->render();
	help->render();
	reset->render();
	knapsack->render();

	for (int i = 0; i < N_ITEMS; i++)
	{
		itemShadow[i]->render();
		if(!knapsackItem[i].inside)
			knapsackItem[i].itemTexture->render();
	}

	maxW->render();
	currW->render();
	totVal->render();
}

void Knapsack::handleEvent(SDL_Event* e)
{
	help->handleEvent(e);
	knapsack->handleEvent(e);

	if (reset->handleEvent(e))
		resetLevel();

	for (int i = 0; i < N_ITEMS; i++)
	{
		if(!knapsackItem[i].inside)
			knapsackItem[i].itemTexture->handleEvent(e);
	}
}

void Knapsack::update()
{
	if (!checkWin())
		updateItems();
	else {
		gameWin = true;
	}
}

bool Knapsack::checkWin()
{
	if (knapsackItem[REGUA].inside && knapsackItem[TESOURA].inside && knapsackItem[LAPIS].inside)
		return true;
	else
		return false;
}

bool Knapsack::gameWon()
{
	return gameWin;
}

void Knapsack::updateItems()
{
	for (int i = 0; i < N_ITEMS; i++)
	{
		if (knapsackItem[i].itemTexture->dropped()) {
			if (knapsack->isWithinBoundaries()) {
				//printf("Item dropped within boundaries\n");
				if (currWeight + knapsackItem[i].weight <= maxWeight)
				{
					packItem(&knapsackItem[i]);
					//printf("Current Weight: %d Tot value: %d\n", currWeight, totValue);
				}
			}
			knapsackItem[i].itemTexture->resetPosition();
		}

		//if (knapsackItem[i].itemTexture->grabbed()) {
		//}
		else {
			knapsackItem[i].itemTexture->updatePosFromMouseState();
		}
		
	}
}

bool Knapsack::packItem(Item* item)
{
	totValue += item->value;
	totVal->loadText(std::to_string(totValue), branco, Game::consolas, 30);

	currWeight += item->weight;
	currW->loadText(std::to_string(currWeight), branco, Game::consolas, 30);

	item->inside = true;

	return true;
}

void Knapsack::resetLevel()
{
	for (int i = 0; i < N_ITEMS; i++)
	{
		unpackItem(&knapsackItem[i]);
	}
	currWeight = 0;
	currW->loadText(std::to_string(currWeight), branco, Game::consolas, 30);
	totValue = 0;
	totVal->loadText(std::to_string(totValue), branco, Game::consolas, 30);
}

bool Knapsack::unpackItem(Item* item)
{
	item->itemTexture->resetPosition();
	item->inside = false;
	return true;
}