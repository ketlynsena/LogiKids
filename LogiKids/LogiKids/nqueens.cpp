#include "nqueens.h"

N_Queens::N_Queens()
{
	background = new GameObject("assets/fundo_nrainhas.png", 0, 0);
	board_texture = new GameObject("assets/tabuleiro.png", 360, 150);
	queen = new Sprite("assets/rainha.png", 360, 150);
}

N_Queens::~N_Queens()
{
}

void N_Queens::handleEvent(SDL_Event* e) 
{
	queen->handleEvent(e);
}

void N_Queens::update() 
{
	queen->update();
}

void N_Queens::render() 
{
	background->render();
	board_texture->render();
	queen->render();
}