#pragma once
#include "SFML/Graphics.hpp"
class GameObject
{
public:
	GameObject();

	virtual void update(float _deltaTime) = 0;
	virtual void draw(sf::RenderWindow& _window);

	bool isActive;
	sf::Vector2f position;
	sf::Vector2f direction;
};

