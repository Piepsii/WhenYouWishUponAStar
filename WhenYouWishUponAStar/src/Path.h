#pragma once

#include <vector>
#include "Node.h"
#include "Grid.h"

class Path
{
public:
	Path(Grid& _grid, int _sX, int _sY, int _tX, int _tY);

	void find();

private:
	Node* start;
	Node* target;
	std::vector<Node> open;
	std::vector<Node> closed;
	Grid* grid;
};

