#include "Cell.h"
#include "StaticVariables.h"

Cell::Cell(int _x, int _y, float _width, float _height)
	: x(_x)
	, y(_y)
	, width(_width + (2 * outlineThickness))
	, height(_height + (2 * outlineThickness))
{
	sf::Vector2f rect = sf::Vector2f(width,
									 height);
	shape = sf::RectangleShape(rect);
	shape.setFillColor(normalColor);
	shape.setPosition(x * (width),
					   y * (height));
	shape.setOutlineColor(outlineColor);
	shape.setOutlineThickness(outlineThickness);

	if (rand() % 100 < 20) {
		isBlocked = true;
	}

	if (isBlocked)
		shape.setFillColor(blockedColor);
	else
		node = std::make_unique<Node>(*this);
}

void Cell::update(float _deltaTime)
{
}

void Cell::draw(sf::RenderWindow& _window)
{
	_window.draw(shape);
	if(node)
		node->draw(_window);
}

Node* Cell::getNode()
{
	return node.get();
}
