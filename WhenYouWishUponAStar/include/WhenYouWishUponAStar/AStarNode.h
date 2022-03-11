#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "WhenYouWishUponAStar/GameObject.h"

namespace WhenYouWishUponAStar {

	class Cell;

	class AStarNode : public GameObject
	{
	public:
		AStarNode(Cell& _cell);
		void update(float _deltaTime);
		void draw(sf::RenderWindow& _window);
		void setColor(sf::Color _color);
		void drawPath();

		int x;
		int y;
		int f = INT_MAX;
		int g = 0;
		int h = INT_MAX;
		AStarNode* parent;

	private:
		Cell* cell;
		std::vector<sf::RectangleShape> edges;
		sf::CircleShape shape;
	};
}
