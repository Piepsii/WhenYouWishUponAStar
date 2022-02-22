#include "Node.h"
#include <random>

Node::Node()
{
	pos.x = 0;
	pos.y = 0;
}

Node::Node(int _x,
		   int _y,
		   float _width,
		   float _height)
{
	pos.x = _x;
	pos.y = _y;
	width = _width;
	height = _height;

	center = sf::CircleShape(width / 4);
	center.setFillColor(sf::Color::Cyan);
	center.setPosition(pos.x * width,
					   pos.y * height);
	center.setOrigin(width / 2,
					 height / 2);
	if (rand() % 100 < 20) {
		isBlocked = true;
	}

}

void Node::update(float _deltaTime)
{
	if (isBlocked)
		center.setFillColor(sf::Color::Red);
}

void Node::draw(sf::RenderWindow& _window)
{
	_window.draw(center);
}
