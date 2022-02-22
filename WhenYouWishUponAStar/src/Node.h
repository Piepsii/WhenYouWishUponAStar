#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Node
{
public:
	Node();
	Node(int _x,
		 int _y,
		 float _width = 32.f,
		 float _height = 32.f);
	void update(float _deltaTime);
	void draw(sf::RenderWindow& _window);

	bool isBlocked = false;

private:
	float width = 32.f;
	float height = 32.f;
	sf::Vector2i pos;
	sf::CircleShape center;
	std::vector<sf::RectangleShape> edges;
};

