#include "WhenYouWishUponAStar/Cell.h"
#include "WhenYouWishUponAStar/StaticVariables.h"

namespace WhenYouWishUponAStar {

	Cell::Cell(int _x, int _y)
		: x(_x)
		, y(_y)
	{
		width = WIDTH / COLUMNS;
		height = HEIGHT / ROWS;
		float innerWidth = WIDTH / COLUMNS - 2 * outlineThickness;
		float innerHeight = HEIGHT / ROWS - 2 * outlineThickness;
		sf::Vector2f rect = sf::Vector2f(innerWidth,
										 innerHeight);
		shape = sf::RectangleShape(rect);
		shape.setFillColor(normalColor);
		shape.setOutlineThickness(outlineThickness);
		shape.setPosition(x * shape.getLocalBounds().WIDTH + outlineThickness,
						  y * shape.getLocalBounds().HEIGHT + outlineThickness);
		shape.setOutlineColor(outlineColor);

		if (rand() % 100 < 20) {
			isBlocked = true;
		}

		node = std::make_unique<Node>(*this);
	}

	void Cell::update(float _deltaTime)
	{
		if (!isActive)
			return;

		if (isSelected) {
			shape.setOutlineColor(selectedColor);
		}
		else {
			shape.setOutlineColor(outlineColor);
		}

		if (isBlocked) {
			shape.setFillColor(blockedColor);
		}
		else {
			shape.setFillColor(normalColor);
		}
	}

	void Cell::draw(sf::RenderWindow& _window)
	{
		if (!isActive)
			return;

		_window.draw(shape);
		if (node)
			node->draw(_window);
	}

	Node* Cell::getNode()
	{
		return node.get();
	}
}
