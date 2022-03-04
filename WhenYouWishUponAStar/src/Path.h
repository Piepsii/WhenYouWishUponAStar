#pragma once

#include <vector>
#include "Node.h"
#include "Grid.h"

class Path
{
public:
	Path(Grid& _grid, int _sX, int _sY, int _tX, int _tY);

	void find();
	bool isNodeInList(Node* _node, std::vector<Node*> _list);

private:
	Node* start;
	Node* target;
	Node* current;
	std::vector<Node*> open;
	std::vector<Node*> closed;
	Grid* grid;
};

