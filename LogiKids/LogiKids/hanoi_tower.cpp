#include "hanoi_tower.h"

Hanoi_Tower::Hanoi_Tower()
{
	background = new GameTexture("assets/hanoi/bolo_de_hanoi.png", 0, 0, false, false);
	help = new GameTexture("assets/buttons/help", 740, 540, true, false);
	reset = new GameTexture("assets/buttons/reset", 15, 540, true, false);

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

	// Render selected layer on top
	for (int i = 0; i < N_LAYERS; i++)
		if (cake_layer[i]->isGrabbed())
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
	gameWin = false;

}

void Hanoi_Tower::update()
{
	if(!checkWin())
		updateLayers();
	else {
		gameWin = true;
	}
}

bool Hanoi_Tower::gameWon()
{
	return gameWin;
}

bool Hanoi_Tower::checkWin()
{
	for (int i = 0; i < N_LAYERS; i++)
	{
		if (tower[i][N_TOWERS - 1] < 1)
			return false;

	}
	return true;
}

void Hanoi_Tower::updateLayers()
{
	// Update each cake layer
	for (int i = 0; i < N_LAYERS; i++)
	{
		// If layer was dropped
		if (cake_layer[i]->dropped()) {
			// Check where it was dropped
			currentIndex = getTowerIndex(cake_layer[i]);

			// If outside boundaries of towers, reset to last grab position
			if (currentIndex.layer < 0)
			{
				placeLayeronTower(cake_layer[i], i, grabIndex);
			}
			else {
				// If the layer index on tower is empty, place cake layer
				
				if (!placeLayeronTower(cake_layer[i], i, currentIndex))
				{
					placeLayeronTower(cake_layer[i], i, grabIndex);
				}
				
			}
			//printTower();
		}
		// If cake was grabbed, save index for drop updates
		if (cake_layer[i]->grabbed()) {
			grabIndex = getTowerIndex(cake_layer[i]);
			tower[grabIndex.layer][grabIndex.n_tower] = 0; // Free layer index
			//printf("Layer grabbed at tower %d, layer %d.\n", grabIndex.n_tower, grabIndex.layer);
			freeLayer = noLayerOnTop(grabIndex);
		}
		// Grab and move cake layer
		if (freeLayer){//isLayerOnTop(grabIndex)) {
			cake_layer[i]->updatePosFromMouseState();
		}			
	}
}

bool Hanoi_Tower::noLayerOnTop(TowerIndex index)
{
	if (index.layer > 0) // If layer not on upper layer, has to check if there is no other layer on top
	{
		for (int i = index.layer; i >= 0; --i) {
			if (tower[i][index.n_tower] > 0) {
				//printf("Layer on top\n");
				return false; // There is at least one layer on top of this one
			}
		}
	}	
	return true;
}

void Hanoi_Tower::printTower()
{
	for (int i = 0; i < N_LAYERS; i++)
	{
		for (int j = 0; j < N_TOWERS; j++)
		{
			printf("%d  ", tower[i][j]);
		}
		printf("\n");
	}	
}

bool Hanoi_Tower::placeLayeronTower(GameTexture* layer, int layerSize, TowerIndex index) {

	int x, y;
	SDL_Point currPos = layer->getCurrentPosition();
	TowerIndex currLayerIndex;

	currLayerIndex.n_tower = index.n_tower;

	//printf("Placing layer with size %d\n", layerSize+1);

	//printTower();
	x = index.n_tower * (TOWER_WIDTH / N_TOWERS) + TOWER_X;

	for (int i = N_LAYERS-1; i >= 0; i--)
	{
		if (tower[i][index.n_tower] < 1) {
			// Found an empty spot
			// Check if layer below is larger than the layer
			currLayerIndex.layer = i;
			if (layerBelowIsLarger(layerSize + 1, currLayerIndex))
			{
				//printf("Free layer %d at tower %d\n", i, index.n_tower);
				y = i * (TOWER_HEIGHT / N_LAYERS) + TOWER_Y;
				tower[i][index.n_tower] = layerSize + 1;
				layer->setPosition(x, y);
				return true;
			}
			else {
				return false;
			}			
		}
	}	
	return false;
}

bool Hanoi_Tower::layerBelowIsLarger(int layerSize, TowerIndex index)
{
	if (index.layer < N_LAYERS - 1) // If not last layer
	{
		//printf("Layer below is Size %d, Layer is size %d\n", tower[index.layer + 1][index.n_tower], layerSize);
		if (layerSize < tower[index.layer + 1][index.n_tower])
		{			
			return true;
		}
		else
			return false;
	}
	
	else // Returns true if tower is empty
	{
		//printf("Last layer, does not matter the size.\n");
		return true;
	}
	
}
