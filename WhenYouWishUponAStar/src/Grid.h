#pragma once

#include <array>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "Node.h"
#include "Cell.h"

class Grid : public GameObject
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
	Cell* getCell(int _x, int _y);

private:
	const static uint32_t columns = 10;
	const static uint32_t rows = 10;
	const static uint32_t size = columns * rows;
	const static uint32_t edgeAmount = 2 * size - columns - rows;
	std::unique_ptr<Cell> cells[size];

	sf::RectangleShape edges[edgeAmount];
};

