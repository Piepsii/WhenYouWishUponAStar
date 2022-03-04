#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "GameObject.h"

class Cell;

class Node : public GameObject
{
public:
	Node(Cell& _cell);
	void update(float _deltaTime);
	void draw(sf::RenderWindow& _window);
	void setColor(sf::Color _color);

	int x;
	int y;
	int f = INT_MAX;
	int g = INT_MAX;
	int h = INT_MAX;

private:
	Cell* cell;
	Node* parent;
	std::vector<sf::RectangleShape> edges;
	sf::CircleShape shape;
};

