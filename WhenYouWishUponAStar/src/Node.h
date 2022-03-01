#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Cell;

class Node
{
public:
	Node();
	void update(float _deltaTime);
	void draw(sf::RenderWindow& _window);

	bool isBlocked = false;

private:
	int h;
	int g;
	int f;
	Cell* cell;
	Node* parent;
	std::vector<sf::RectangleShape> edges;
};

