#include <random>

#include "WhenYouWishUponAStar/AStarNode.h"
#include "WhenYouWishUponAStar/Cell.h"

namespace WhenYouWishUponAStar {

	AStarNode::AStarNode(Cell& _cell)
	{
		cell = &_cell;
		x = cell->x;
		y = cell->y;
		float radius = cell->width / 6;
		shape = sf::CircleShape(radius);
		shape.setFillColor(sf::Color::White);
		drawPosition.x = cell->x * cell->width + cell->width / 2;
		drawPosition.y = cell->y * cell->height + cell->height / 2;
		shape.setPosition(drawPosition);
		shape.setOrigin(radius,
						radius);
	}

	void AStarNode::update(float _deltaTime)
	{
		if (!isActive)
			return;

	}

	void AStarNode::draw(sf::RenderWindow& _window)
	{
		if (!isActive)
			return;

		_window.draw(shape);
		for (auto& edge : edges)
			_window.draw(edge);
	}

	void AStarNode::setColor(sf::Color _color)
	{
		shape.setFillColor(_color);
	}

	void AStarNode::drawPath()
	{
		setColor(sf::Color::Green);
		if (parent) {
			addEdge(this, parent);
			parent->drawPath();
		}
	}

	void AStarNode::addEdge(AStarNode* _start, AStarNode* _end)
	{
		sf::Vector2f position = _start->drawPosition;
		sf::Vector2f length = _end->drawPosition - _start->drawPosition;
		float magnitude = sqrtf(length.x * length.x + length.y * length.y);
		sf::Vector2f size = sf::Vector2f(magnitude, lineThickness);
		float angle = atan2(length.y, length.x);
		float angleInDegree = angle * 180.0f / 3.14159265358979323846f;

		sf::RectangleShape edge = sf::RectangleShape(size);
		edge.setOrigin(0.0f, lineThickness / 2.0f);
		edge.setRotation(angleInDegree);
		edge.setPosition(position);
		edge.setFillColor(sf::Color::Green);
		edges.push_back(edge);
	}
}
