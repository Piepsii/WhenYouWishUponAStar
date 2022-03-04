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
	Node* getNode();

	bool isBlocked = false;
	int x;
	int y;
	float width = 32.f;
	float height = 32.f;

private:
	float outlineThickness = 3.5f;
	std::unique_ptr<Node> node;
	sf::RectangleShape shape;
	sf::Color normalColor = sf::Color::White;
	sf::Color blockedColor = sf::Color::Black;
	sf::Color outlineColor = sf::Color::Black;

};

