#include "balance_scale.h"
#include "game.h"

BalanceScale::BalanceScale()
{
	background = new GameTexture("assets/scale_weights/peso_misterioso.png", 0, 0, false, false);
	help = new GameTexture("assets/buttons/help", 740, 540, true, false);
	reset = new GameTexture("assets/buttons/reset", 15, 540, true, false);

	// Botao para pesagem da balança
	button = new GameTexture("assets/scale_weights/sprites/botao", 391, 406, true, false);

	// Texturas balança
	scale[LEVEL]	  = new GameTexture("assets/scale_weights/balanca_equilibrada.png", 202, 338, false, false);
	scale[LEAN_LEFT]  = new GameTexture("assets/scale_weights/balanca_esquerda.png", 202, 338, false, false);
	scale[LEAN_RIGHT] = new GameTexture("assets/scale_weights/balanca_direita.png", 202, 338, false, false);

	weighs[0] = new GameTexture("assets/scale_weights/zero.png", 393, 441, false, false);
	weighs[1] = new GameTexture("assets/scale_weights/um.png", 393, 441, false, false);
	weighs[2] = new GameTexture("assets/scale_weights/dois.png", 393, 441, false, false);

	solution_area = new GameTexture("assets/scale_weights/peso_sombra.png", 582, 190, false, false);

	// Texturas dos pesos
	for (int i = 0; i < N_WEIGHTS; i++)
	{
		weight[i] = new GameTexture("assets/scale_weights/sprites/peso", 192 + (i * 55), 505, true, true);
	}
}

BalanceScale::~BalanceScale()
{
}

void BalanceScale::render()
{
	background->render();
	help->render();
	reset->render();
	solution_area->render();

	scale[scale_state]->render();
	button->render();

	weighs[n_weighs]->render();

	for (int i = 0; i < N_WEIGHTS; i++)
	{
		weight[i]->render();
	}
}

void BalanceScale::handleEvent(SDL_Event* e)
{
	help->handleEvent(e);
	button->handleEvent(e);

	if (reset->handleEvent(e))
		resetLevel();

	for (int i = 0; i < N_WEIGHTS; i++)
	{
		weight[i]->handleEvent(e);
	}
}

void BalanceScale::update()
{
	//if (!checkWin())
	//	updateItems();
	//else {
	//	gameWin = true;
	//}
}

int BalanceScale::getScaleState()
{
	return scale_state;
}

void BalanceScale::setScaleState(int state)
{
	if(state >= 0 && state < 3)
		scale_state = state;
}

void BalanceScale::resetLevel()
{
}

bool BalanceScale::checkWin()
{
	return false;
}

bool BalanceScale::gameWon()
{
	return gameWin;
}
