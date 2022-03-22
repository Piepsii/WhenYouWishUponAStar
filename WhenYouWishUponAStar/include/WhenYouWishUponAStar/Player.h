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
		sf::Vector2i getHovered();
		sf::Vector2i getSelected();

		bool usesAStar = false;
		bool needsPause = true;
		bool isDragging = false;
		bool hasSelected = false;
		bool hasUpdatedGrid = false;
		InputManager* input = nullptr;
		Grid* grid = nullptr;
	private:
		int hoverX = 0;
		int hoverY = 0;
		int previousX = -1;
		int previousY = -1;
		sf::Vector2i selected;
		Cell* selectedCell;
	};
}
