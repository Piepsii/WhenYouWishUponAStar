#include "WhenYouWishUponAStar/Path.h"

namespace WhenYouWishUponAStar {

	Path::Path(GameObject* _parent, const ComponentFamilyId _id)
		: ComponentBase(_parent, _id)
	{

	}

	Path::~Path()
	{

	}

	void Path::setupPath(Grid& _grid, int _sX, int _sY, int _tX, int _tY)
	{
		grid = &_grid;

		Cell* startCell = grid->getCell(_sX, _sY);
		if (startCell->isBlocked)
			startCell = grid->getRandomCell();
		start = startCell->getNode();
		start->setColor(sf::Color::Blue);

		Cell* targetCell = grid->getCell(_tX, _tY);
		if (targetCell->isBlocked)
			targetCell = grid->getRandomCell();
		target = targetCell->getNode();
		target->setColor(sf::Color::Blue);

		current = nullptr;
	}

	Node* Path::find()
	{
		open.push_back(start);
		current = start;
		std::vector<Cell*> neighborCells = grid->getAllNeighbors(current->x,
																 current->y);
		std::vector<Node*> neighbors;
		for (int i = 0; i < neighborCells.size(); i++) {
			if (!neighborCells[i]->isBlocked)
				neighbors.push_back(neighborCells[i]->getNode());
		}
		for (int i = 0; i < neighbors.size(); i++) {
			neighbors[i]->parent = current;
			if (isNodeInList(neighbors[i], closed)) {
				continue;
			}
			// g
			int distanceX = neighbors[i]->x - current->x;
			int distanceY = neighbors[i]->y - current->y;
			float magnitude = sqrtf(abs(distanceX) + abs(distanceY));
			if (magnitude > 1.4f) {
				neighbors[i]->g = current->g + 14;
			}
			else {
				neighbors[i]->g = current->g + 10;
			}
			// h
			neighbors[i]->h = manhattan(neighbors[i]->x, neighbors[i]->y);

			// f
			neighbors[i]->f = neighbors[i]->g + neighbors[i]->h;

			open.push_back(neighbors[i]);
		}
		while (current->x != target->x || current->y != target->y) {
			int lowest = INT_MAX;
			int lowestIndex = -1;
			for (int i = 0; i < open.size(); i++) {
				if (open[i]->f < lowest) {
					lowest = open[i]->f;
					lowestIndex = i;
				}
			}
			current = open.at(lowestIndex);
			open.erase(open.begin() + lowestIndex);
			if (current == target) {
				target->drawPath();
				return target;
			}

			closed.push_back(current);
			std::vector<Cell*> neighborCells = grid->getAllNeighbors(current->x,
																	 current->y);
			std::vector<Node*> neighbors;
			for (int i = 0; i < neighborCells.size(); i++) {
				if (!neighborCells[i]->isBlocked)
					neighbors.push_back(neighborCells[i]->getNode());
			}
			for (int i = 0; i < neighbors.size(); i++) {
				if (isNodeInList(neighbors[i], closed)) {
					continue;
				}
				// g
				int distanceX = neighbors[i]->x - current->x;
				int distanceY = neighbors[i]->y - current->y;
				float magnitude = sqrtf(abs(distanceX) + abs(distanceY));
				if (magnitude > 1.4f) {
					neighbors[i]->g = current->g + 14;
				}
				else {
					neighbors[i]->g = current->g + 10;
				}
				// h
				neighbors[i]->h = manhattan(neighbors[i]->x, neighbors[i]->y);

				// f
				neighbors[i]->f = neighbors[i]->g + neighbors[i]->h;

				if (isNodeInList(neighbors[i], open) && neighbors[i]->g > current->g) {
					continue;
				}
				neighbors[i]->parent = current;
				open.push_back(neighbors[i]);
			}
		}

	}

	bool Path::isNodeInList(Node* _node, std::vector<Node*> _list)
	{
		for (int i = 0; i < _list.size(); i++) {
			if (_list[i] == _node)
				return true;
		}
		return false;
	}

	int Path::manhattan(int _x, int _y)
	{
		return abs(target->x - _x + target->y - _y) * 10;
	}
}
