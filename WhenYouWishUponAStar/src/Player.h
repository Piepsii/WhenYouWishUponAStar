#pragma once

#include "GameObject.h"
#include "InputManager.h"

class Player : public GameObject
{
public:
	Player();
	void update(float _deltaTime);

	InputManager* input;
private:

};

