#include "Node.h"

#include <random>

#include "Cell.h"

Node::Node(Cell& _cell)
{
	cell = &_cell;
	x = cell->x;
	y = cell->y;
	float radius = cell->width / 3;
	shape = sf::CircleShape(radius);
	shape.setFillColor(sf::Color::White);
	shape.setPosition(cell->x * cell->width + cell->width / 2,
					  cell->y * cell->height + cell->height / 2);
	shape.setOrigin(radius,
					radius);
}

void Node::update(float _deltaTime)
{
	if (!isActive)
		return;

}

void Node::draw(sf::RenderWindow& _window)
{
	if (!isActive)
		return;

	_window.draw(shape);
}

void Node::setColor(sf::Color _color)
{
	shape.setFillColor(_color);
}

void Node::drawPath()
{
	setColor(sf::Color::Green);
	if (parent) {
		parent->drawPath();
	}
}
