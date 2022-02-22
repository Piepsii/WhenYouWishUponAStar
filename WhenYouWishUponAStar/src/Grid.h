#pragma once

#include <array>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Node.h"

class Grid
{
public:
	Grid();
	void update(float _deltaTime);
	void draw(sf::RenderWindow& _window);
	uint32_t Columns();
	uint32_t Rows();
	uint32_t Size();
	sf::Vector2i GetRandomNeighbor(sf::Vector2i _pos);
	uint32_t GetRandomNeighborAsIndex(sf::Vector2i _pos);

private:
	const static uint32_t columns = 10;
	const static uint32_t rows = 10;
	const static uint32_t size = columns * rows;
	Node graph[size];
};

