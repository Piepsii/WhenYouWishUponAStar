#include "Cell.h"

Cell::Cell(int _x, int _y, float _width, float _height)
{
	width = _width;
	height = _height;

	center = sf::CircleShape(width / 4);
	center.setFillColor(sf::Color::Cyan);
	center.setPosition(_x * width,
					   _y * height);
	center.setOrigin(width / 2,
					 height / 2);
	node = std::make_unique<Node>();
}

void Cell::update(float _deltaTime)
{
	if (node->isBlocked)
		center.setFillColor(sf::Color::Red);
}

void Cell::draw(sf::RenderWindow& _window)
{
	_window.draw(center);
}
