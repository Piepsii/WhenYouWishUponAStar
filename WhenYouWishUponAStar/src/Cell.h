#pragma once

#include "Node.h"

class Cell
{
public:
	Cell(int _x = 0,
		 int _y = 0,
		 float _width = 32.f,
		 float _height = 32.f);
	void update(float _deltaTime);
	void draw(sf::RenderWindow& _window);

	int x;
	int y;
	std::unique_ptr<Node> node;

private:
	float width = 32.f;
	float height = 32.f;
	sf::CircleShape center;

};

