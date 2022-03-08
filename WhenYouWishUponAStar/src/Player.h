#pragma once

#include "GameObject.h"
#include "InputManager.h"
#include "Grid.h"

class Player : public GameObject
{
public:
	Player();
	void update(float _deltaTime);
	void handleInput();

	bool hasUpdatedGrid = false;
	InputManager* input = nullptr;
	Grid* grid = nullptr;
private:
	int selectX = 0;
	int selectY = 0;
	int previousX = -1;
	int previousY = -1;
	Cell* selectedCell;
};

