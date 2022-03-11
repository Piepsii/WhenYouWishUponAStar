#pragma once

#include "WhenYouWishUponAStar/GameObject.h"
#include "WhenYouWishUponAStar/AStarNode.h"

namespace WhenYouWishUponAStar {
	class Cell : public GameObject
	{
	public:
		Cell(int _x = 0,
			 int _y = 0);
		void update(float _deltaTime);
		void draw(sf::RenderWindow& _window);

		bool isBlocked = false;
		bool isSelected = false;
		int x;
		int y;
		float width = 0.0f;
		float height = 0.0f;

	private:
		int blockChance = 40;
		float outlineThickness = 3.0f;
		sf::RectangleShape shape;
		sf::Color normalColor = sf::Color::Black;
		sf::Color blockedColor = sf::Color::White;
		sf::Color outlineColor = sf::Color::White;
		sf::Color selectedColor = sf::Color::Blue;

	};
}

