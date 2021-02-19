#include "hanoi_tower.h"

Hanoi_Tower::Hanoi_Tower()
{
	background = new GameTexture("assets/hanoi/bolo_de_hanoi.png", 0, 0, false, false);
	help = new GameTexture("assets/buttons/help", 740, 540, true, false);
	reset = new GameTexture("assets/buttons/reset", 15, 550, true, false);

	candle[0] = new GameTexture("assets/hanoi/vela_azul.png", 158, 233, false, false);
	candle[1] = new GameTexture("assets/hanoi/vela_roxa.png", 395, 233, false, false);
	candle[2] = new GameTexture("assets/hanoi/vela_vermelha.png", 630, 233, false, false);

	cake_layer[0] = new GameTexture("assets/hanoi/bolo_1.png", 45, 277, false, true);//124, 277, false, true);
	cake_layer[1] = new GameTexture("assets/hanoi/bolo_2.png", 45, 336, false, true);//93, 336, false, true);
	cake_layer[2] = new GameTexture("assets/hanoi/bolo_3.png", 45, 395, false, true);//67, 395, false, true);
	cake_layer[3] = new GameTexture("assets/hanoi/bolo_4.png", 45, 454, false, true);//45, 454, false, true);	
	
	for (int i = 0; i < N_LAYERS; i++)
		tower[i][0] = i + 1;
}

Hanoi_Tower::~Hanoi_Tower()
{
}

void Hanoi_Tower::render()
{
	background->render();
	help->render();
	reset->render();

	for (int i = 0; i < 3; i++)
		candle[i]->render();

	for (int i = 0; i < N_LAYERS; i++)
		cake_layer[i]->render();
}

void Hanoi_Tower::handleEvent(SDL_Event* e)
{
	help->handleEvent(e);

	if (reset->handleEvent(e))
		resetLevel();

	for (int i = 0; i < N_LAYERS; i++)
	{
		cake_layer[i]->handleEvent(e);
	}
}

TowerIndex Hanoi_Tower::getTowerIndex(GameTexture* layer)
{
	TowerIndex index;
	SDL_Point layerPos = layer->getCurrentPosition();	

	int layerCenterX = layerPos.x + (layer->getWidth() / 2),
		layerCenterY = layerPos.y + (layer->getHeight() / 2);

	// If inside boundaries of towers
	if (((layerCenterX >= TOWER_X && layerCenterX < TOWER_X + TOWER_WIDTH)) && 
		(layerCenterY >= TOWER_Y && layerCenterY < (TOWER_Y + TOWER_HEIGHT)))
	{
		index.n_tower = (layerCenterX - TOWER_X) / (TOWER_WIDTH / N_TOWERS);
		index.layer = (layerCenterY - TOWER_Y) / (TOWER_HEIGHT / N_LAYERS);
	}
	else {
		
		index.layer = -1;
		index.n_tower = -1;
	}
	return index;	
}

void Hanoi_Tower::resetLevel()
{	
	for (int i = 0; i < N_LAYERS; i++)
		for (int j = 0; j < 3; j++)
			tower[i][j] = 0;

	for (int i = 0; i < N_LAYERS; i++) {
		cake_layer[i]->resetPosition();
		tower[i][0] = i + 1;
	}

}

void Hanoi_Tower::update()
{
	for (int i = 0; i < N_LAYERS; i++)
	{
		cake_layer[i]->updatePosFromMouseState();
		if (cake_layer[i]->dropped()) {
			currentIndex = getTowerIndex(cake_layer[i]);
			if (currentIndex.layer < 0)
			{
				cake_layer[i]->resetPosition();
			}
			else {
				placeLayeronTower(cake_layer[i], currentIndex);
				printf("Layer dropped at tower %d, layer %d.\n", currentIndex.n_tower, currentIndex.layer);
			}	
		}
		if (cake_layer[i]->grabbed()) {
			currentIndex = getTowerIndex(cake_layer[i]);
			printf("Layer grabbed at tower %d, layer %d.\n", currentIndex.n_tower, currentIndex.layer);
		}
	}
}

bool Hanoi_Tower::placeLayeronTower(GameTexture* layer, TowerIndex index) {

	int x, y;
	SDL_Point currPos = layer->getCurrentPosition();

	//x = currPos.x + index.n_tower * (TOWER_WIDTH / N_TOWERS);
	//y = currPos.y + index.layer * (TOWER_HEIGHT / N_LAYERS);
	x = index.n_tower * (TOWER_WIDTH / N_TOWERS) + TOWER_X;
	y = index.layer * (TOWER_HEIGHT / N_LAYERS) + TOWER_Y;

	layer->setPosition(x, y);

	return true;
}
