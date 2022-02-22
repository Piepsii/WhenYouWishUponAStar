#include "Grid.h"
#include "StaticVariables.h"

Grid::Grid()
{
	float nodeWidth = WIDTH / columns;
	float nodeHeight = HEIGHT / rows;

	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			graph[j * columns + i] = Node(i, j, nodeWidth, nodeHeight);
		}
	}

	for (int i = 0; i < columns - 1; i++) {
		for (int j = 0; j < rows - 1; j++) {
		}
	}
}

void Grid::update(float _deltaTime)
{
	for (int i = 0; i < size; i++) {
		graph[i].update(_deltaTime);
	}
}

void Grid::draw(sf::RenderWindow& _window)
{
	for (int i = 0; i < size; i++) {
		graph[i].draw(_window);
	}
}

uint32_t Grid::Columns()
{
	return columns;
}

uint32_t Grid::Rows()
{
	return rows;
}

uint32_t Grid::Size()
{
	return columns * rows;
}

sf::Vector2i Grid::GetRandomNeighbor(sf::Vector2i _pos)
{
	int neighborX = -1, neighborY = -1;
	while (neighborX < 0 || neighborX >= columns) {
		int offsetX = rand() % 3 - 1;
		neighborX = _pos.x + offsetX;
	}
	while (neighborY < 0 || neighborY >= rows) {
		int offsetY = rand() % 3 - 1;
		neighborY = _pos.y + offsetY;
	}
	sf::Vector2i result = { neighborX, neighborY };
	return result;
}

uint32_t Grid::GetRandomNeighborAsIndex(sf::Vector2i _pos)
{
	int neighborX = -1, neighborY = -1;
	while (neighborX < 0 || neighborX >= columns) {
		int offsetX = rand() % 3 - 1;
		neighborX = _pos.x + offsetX;
	}
	while (neighborY < 0 || neighborY >= rows) {
		int offsetY = rand() % 3 - 1;
		neighborY = _pos.y + offsetY;
	}

	uint32_t index = neighborY * columns + neighborX;
	return index;
}
