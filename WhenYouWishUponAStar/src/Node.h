#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Cell;

class Node
{
public:
	Node(Cell& _cell);
	void update(float _deltaTime);
	void draw(sf::RenderWindow& _window);
	void setColor(sf::Color _color);

private:
	int h = INT_MAX;
	int g = INT_MAX;
	int f = INT_MAX;
	Cell* cell;
	Node* parent;
	std::vector<sf::RectangleShape> edges;
	sf::CircleShape shape;
};

