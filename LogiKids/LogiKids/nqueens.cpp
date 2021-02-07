#include "nqueens.h"

N_Queens::N_Queens()
{
	background = new GameObject("assets/fundo_nrainhas.png", 0, 0);
	board_texture = new GameObject("assets/tabuleiro.png", 360, 150);
}

N_Queens::~N_Queens()
{
}

void N_Queens::handleEvent(SDL_Event* e) 
{

}

void N_Queens::update() 
{

}

void N_Queens::render() 
{
	background->render();
	board_texture->render();
}