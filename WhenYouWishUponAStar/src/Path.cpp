#include "Path.h"

Path::Path(Grid& _grid, int _sX, int _sY, int _tX, int _tY)
{
	grid = &_grid;

	Cell* startCell = grid->getCell(_sX, _sY);
	start = startCell->getNode();

	Cell* targetCell = grid->getCell(_tX, _tY);
	target = targetCell->getNode();
}

void Path::find()
{
	start->setColor(sf::Color::Red);
	target->setColor(sf::Color::Blue);
}
