#pragma once

#include "GameObject.h"
#include "Node.h"

class Cell : public GameObject
{
public:
	Cell(int _x = 0,
		 int _y = 0);
	void update(float _deltaTime);
	void draw(sf::RenderWindow& _window);
	Node* getNode();

	bool isBlocked = false;
	bool isSelected = false;
	int x;
	int y;
	float width = 0.0f;
	float height = 0.0f;

private:
	float outlineThickness = 3.0f;
	std::unique_ptr<Node> node;
	sf::RectangleShape shape;
	sf::Color normalColor = sf::Color::White;
	sf::Color blockedColor = sf::Color::Black;
	sf::Color outlineColor = sf::Color::Black;
	sf::Color selectedColor = sf::Color::Yellow;

};

