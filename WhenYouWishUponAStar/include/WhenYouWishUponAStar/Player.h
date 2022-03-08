#pragma once

#include "WhenYouWishUponAStar/GameObject.h"
#include "WhenYouWishUponAStar/InputManager.h"
#include "WhenYouWishUponAStar/Grid.h"

namespace WhenYouWishUponAStar {

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
}
