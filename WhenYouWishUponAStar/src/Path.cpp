#include "Path.h"

Path::Path(Grid& _grid, int _sX, int _sY, int _tX, int _tY)
{
	grid = &_grid;

	Cell* startCell = grid->getCell(_sX, _sY);
	startCell = grid->getRandomCell();
	start = startCell->getNode();

	Cell* targetCell = grid->getCell(_tX, _tY);
	targetCell = grid->getRandomCell();
	target = targetCell->getNode();
}

void Path::find()
{
	start->setColor(sf::Color::Red);
	target->setColor(sf::Color::Blue);
}
