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
	scale_level	  = new GameTexture("assets/scale_weights/balanca_equilibrada.png", 202, 338, false, false);
	scale_left  = new GameTexture("assets/scale_weights/balanca_esquerda.png", 202, 338, false, false);
	scale_right = new GameTexture("assets/scale_weights/balanca_direita.png", 202, 338, false, false);

	weighs[0] = new GameTexture("assets/scale_weights/dois.png", 393, 441, false, false);
	weighs[1] = new GameTexture("assets/scale_weights/um.png", 393, 441, false, false);
	weighs[2] = new GameTexture("assets/scale_weights/zero.png", 393, 441, false, false);

	solution_area = new GameTexture("assets/scale_weights/peso_sombra.png", 582, 190, false, false);

	// Texturas dos pesos
	weight[0] = new GameTexture("assets/scale_weights/sprites/weight1", 192, 505, true, true);
	weight[1] = new GameTexture("assets/scale_weights/sprites/weight2", 192 + (1 * 55), 505, true, true);
	weight[2] = new GameTexture("assets/scale_weights/sprites/weight3", 192 + (2 * 55), 505, true, true);
	weight[3] = new GameTexture("assets/scale_weights/sprites/weight4", 192 + (3 * 55), 505, true, true);
	weight[4] = new GameTexture("assets/scale_weights/sprites/weight5", 192 + (4 * 55), 505, true, true);
	weight[5] = new GameTexture("assets/scale_weights/sprites/weight6", 192 + (5 * 55), 505, true, true);
	weight[6] = new GameTexture("assets/scale_weights/sprites/weight7", 192 + (6 * 55), 505, true, true);
	weight[7] = new GameTexture("assets/scale_weights/sprites/weight8", 192 + (7 * 55), 505, true, true);
}

BalanceScale::~BalanceScale()
{
}

void BalanceScale::renderScale()
{
	switch (getScaleState()) {
	case LEVEL:
		scale_level->render();
		break;
	case LEAN_LEFT:
		scale_left->render();
		break;
	case LEAN_RIGHT:
		scale_right->render();
		break;
	default:
		scale_level->render();
		break;
	}
}

void BalanceScale::render()
{
	background->render();
	help->render();
	reset->render();
	solution_area->render();

	renderScale();

	button->render();

	weighs[n_weighs]->render();

	for (int i = 0; i < N_WEIGHTS; i++)
	{
		weight[i]->render();
	}
}

void BalanceScale::weigh()
{
	int left_count = 0;
	int right_count = 0;

	if (n_weighs < 2)
		n_weighs++;

	for (int i = 0; i < MAX_WEIGHS_ON_PLATE; i++)
	{
		if((scale_plates[LEFT_PLATE][i] >= 0) && (scale_plates[LEFT_PLATE][i] != lighter_weight))
			left_count++;
		if ((scale_plates[RIGHT_PLATE][i] >= 0) && (scale_plates[RIGHT_PLATE][i] != lighter_weight))
			right_count++;
	}

	if (left_count < right_count)
		setScaleState(LEAN_RIGHT);
	else if( left_count > right_count)
		setScaleState(LEAN_LEFT);
	else 
		setScaleState(LEVEL);
}

void BalanceScale::handleEvent(SDL_Event* e)
{
	help->handleEvent(e);
	if (button->handleEvent(e))
		if(n_weighs < MAX_WEIGHS)
			weigh();

	if (reset->handleEvent(e))
		resetLevel();

	for (int i = 0; i < N_WEIGHTS; i++)
	{
		weight[i]->handleEvent(e);
	}
}

Index BalanceScale::getPlateIndex(GameTexture* w)
{
	Index index;
	SDL_Point weightPos = w->getCurrentPosition();
	int scale_offset = 34 * getScaleState(); // Offset from the changing heights of a balance scale

	int weightCenterX = weightPos.x + (w->getWidth() / 2),
		weightCenterY = weightPos.y + (w->getHeight() / 2);

	index.plate = -1;
	index.n = -1;

	// Check if within boundaries of plates
	if ((weightCenterX >= LEFT_PLATE_X) && (weightCenterX < LEFT_PLATE_X + PLATE_WIDTH)) {
		if ((weightCenterY >= LEVEL_PLATE_Y - (scale_offset)) && (weightCenterY < LEVEL_PLATE_Y - (scale_offset) + PLATE_HEIGHT)) {
			// Weight is on Left Plate
			index.plate = LEFT_PLATE;
			index.n = (weightCenterX - LEFT_PLATE_X) / (PLATE_WIDTH / MAX_WEIGHS_ON_PLATE);				
		}
	}
	else if ((weightCenterX >= RIGHT_PLATE_X) && (weightCenterX < RIGHT_PLATE_X + PLATE_WIDTH)) {
		if ((weightCenterY >= LEVEL_PLATE_Y + (scale_offset)) && (weightCenterY < LEVEL_PLATE_Y + (scale_offset) + PLATE_HEIGHT)) {
			// Weight is on Right Plate
			index.plate = RIGHT_PLATE;
			index.n = (weightCenterX - RIGHT_PLATE_X) / (PLATE_WIDTH / MAX_WEIGHS_ON_PLATE);
		}
	}	
	return index;
}

void BalanceScale::update()
{
	if (!gameWon())
		updateWeights();
	
}

void BalanceScale::addWeightToSolutionArea(GameTexture* w)
{
	SDL_Point areaPos = solution_area->getCurrentPosition();
	w->setPosition(areaPos.x, areaPos.y);
}

bool BalanceScale::checkIfWithinSolutionArea(GameTexture* w)
{
	SDL_Point solArea = solution_area->getCurrentPosition();
	SDL_Point weightPos = w->getCurrentPosition();

	int weightCenterX = weightPos.x + (w->getWidth() / 2),
		weightCenterY = weightPos.y + (w->getHeight() / 2);

	if ((weightCenterX >= solArea.x) && (weightCenterX < solArea.x + solution_area->getWidth()))
		if ((weightCenterY >= solArea.y) && (weightCenterY < solArea.y + solution_area->getHeight()))
			return true;
	return false;
}

void BalanceScale::updateWeights() {
	for (int i = 0; i < N_WEIGHTS; i++)
	{
		if (weight[i]->dropped())
		{
			index = getPlateIndex(weight[i]);
			//printf("Weight dropped at plate %d, n %d.\n", index.plate, index.n);
			if (index.plate < 0)
			{
				if (checkIfWithinSolutionArea(weight[i])) // Dropped in solution area
				{
					//printf("Weight dropped within solutiona area boundaries.\n");
					addWeightToSolutionArea(weight[i]);
					checkWin(i);
				}
				else {
					weight[i]->resetPosition();
				}				
			}
			else {
				if (!addWeightToScale(weight[i], index, i)) {
					weight[i]->resetPosition();
				}
			}
		}
		if (weight[i]->grabbed())
		{
			removeWeightFromScale(i);
		}
		weight[i]->updatePosFromMouseState();
	}
}

void BalanceScale::removeWeightFromScale(int i)
{
	for (int n = 0; n < MAX_WEIGHS_ON_PLATE; n++)
	{
		if (scale_plates[LEFT_PLATE][n] == i)
			scale_plates[LEFT_PLATE][n] = -1;
			
		if (scale_plates[RIGHT_PLATE][n] == i)
			scale_plates[RIGHT_PLATE][n] = -1;
	}	
}

bool BalanceScale::addWeightToScale(GameTexture* w, Index idx, int weight_number)
{
	int scale_offset = 34 * getScaleState(), x_offset;
	int x = -1, y = -1;

	if (idx.plate == LEFT_PLATE)
	{
		x_offset = LEFT_PLATE_X;
		y = LEVEL_PLATE_Y - scale_offset;
	}		
	else
	{
		x_offset = RIGHT_PLATE_X;
		y = LEVEL_PLATE_Y + scale_offset;
	}		

	for (int i = 0; i < MAX_WEIGHS_ON_PLATE; i++)
	{
		if (scale_plates[idx.plate][i] < 0) { // Empty spot
			x = i * (PLATE_WIDTH / MAX_WEIGHS_ON_PLATE) + x_offset;
			scale_plates[idx.plate][i] = weight_number;
			w->setPosition(x, y);
			return true;
		}
	}
	return false;
}

int BalanceScale::getScaleState()
{
	return scale_state;
}

void BalanceScale::setScaleState(int state)
{
	scale_state = state;
	SDL_Point currPos;
	int y = LEVEL_PLATE_Y;
	int scale_offset = 34 * getScaleState();

	for (int i = 0; i < MAX_WEIGHS_ON_PLATE; i++)
	{
		if (scale_plates[LEFT_PLATE][i] >= 0)
		{
			currPos = weight[scale_plates[LEFT_PLATE][i]]->getCurrentPosition();
			weight[scale_plates[LEFT_PLATE][i]]->setPosition(currPos.x, y-scale_offset);

		}
		if (scale_plates[RIGHT_PLATE][i] >= 0)
		{
			currPos = weight[scale_plates[RIGHT_PLATE][i]]->getCurrentPosition();
			weight[scale_plates[RIGHT_PLATE][i]]->setPosition(currPos.x, y + scale_offset);
		}
	}
}

void BalanceScale::resetLevel()
{
	for (int n = 0; n < MAX_WEIGHS_ON_PLATE; n++)
	{		
		scale_plates[LEFT_PLATE][n] = -1;		
		scale_plates[RIGHT_PLATE][n] = -1;
	}

	for (int i = 0; i < N_WEIGHTS; i++)
	{
		weight[i]->resetPosition();
	}

	setScaleState(LEVEL);
	n_weighs = 0;
	wrong_answer = false;
	gameWin = false;
	// Randomizar peso mais leve
}

bool BalanceScale::checkWin(int i)
{
	if (i == lighter_weight)
	{
		gameWin = true;
		return true;
	}		
	else
	{
		wrong_answer = true;
		return false;
	}		
}

bool BalanceScale::gameWon()
{
	return gameWin;
}
