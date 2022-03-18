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
		void draw(sf::RenderWindow& _window);
		void setColor(sf::Color _color);
		void drawPath();
		void addEdge(AStarNode* _start, AStarNode* _end);

		int x;
		int y;
		int f = INT_MAX;
		int g = 0;
		int h = INT_MAX;
		Cell* cell;
		AStarNode* parent;
		sf::Vector2f drawPosition;

	private:
		float lineThickness = 6.0f;
		std::vector<sf::RectangleShape> edges;
		sf::CircleShape shape;
	};
}
