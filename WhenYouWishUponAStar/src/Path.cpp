#include "Path.h"

Path::Path(Grid& _grid, int _sX, int _sY, int _tX, int _tY)
{
	grid = &_grid;

	Cell* startCell = grid->getCell(_sX, _sY);
	start = startCell->getNode();
	start->setColor(sf::Color::Red);

	Cell* targetCell = grid->getCell(_tX, _tY);
	targetCell = grid->getRandomCell();
	target = targetCell->getNode();
	target->setColor(sf::Color::Blue);
}

void Path::find()
{
	open.push_back(start);
	current = start;
	while (current->x != target->y || current->y != target->y) {
		current = open.at(0);
		if (current == target) {
			return;
		}
		else {
			closed.push_back(current);
			std::vector<Cell*> neighborCells = grid->getAllNeighbors(current->x,
																 current->y);
			std::vector<Node*> neighbors;
			for (int i = 0; i < neighborCells.size(); i++) {
				neighbors.push_back(neighborCells[i]->getNode());
			}
			for (int i = 0; i < neighbors.size(); i++) {
				if (neighbors[i]->g < current->g && isNodeInList(neighbors[i], closed)) {
					// replace the neighbor with the new, lower, g value
					//	current node is now the neighbor's parent   
				}
				else if (neighbors[i]->g >= current->g && isNodeInList(neighbors[i], open)) {
					// replace the neighbor with the new, lower, g value
					//	change the neighbor's parent to our current node
				}
				else if(isNodeInList(neighbors[i], closed) && isNodeInList(neighbors[i], open)) {
					// add it to the open listand set its g
				}

			}
		}
		
	}
	//std::sort(open.begin(), open.end(), [](const Node& lhs, const Node& rhs) {
	//	return lhs.f < rhs.f;
	//		  });
}

bool Path::isNodeInList(Node* _node, std::vector<Node*> _list)
{
	for (int i = 0; i < _list.size(); i++) {
		if (_list[i] == _node)
			return true;
	}
	return false;
}
