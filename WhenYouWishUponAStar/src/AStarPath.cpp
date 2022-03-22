#include "WhenYouWishUponAStar/AStarPath.h"

namespace WhenYouWishUponAStar {

	AStarPath::AStarPath(GameObject* _parent, const ComponentFamilyId _id)
		: ComponentBase(_parent, _id)
	{

	}

	AStarPath::~AStarPath()
	{

	}

	void AStarPath::draw(sf::RenderWindow& _window)
	{
		for (auto& node : nodes)
			node->draw(_window);
	}

	void AStarPath::setGrid(Grid& _grid)
	{
		grid = &_grid;
	}

	AStarNode* AStarPath::find(int _sX, int _sY, int _tX, int _tY)
	{
		clear();
		Cell* startCell = grid->getCell(_sX, _sY);
		if (startCell->isBlocked)
			startCell = grid->getRandomCell();

		Cell* targetCell = grid->getCell(_tX, _tY);
		if (targetCell->isBlocked)
			targetCell = grid->getRandomCell();
		start = createNode(*startCell);
		start->setColor(sf::Color::Blue);
		target = createNode(*targetCell);
		target->setColor(sf::Color::Blue);
		current = nullptr;
		open.push_back(start);
		current = start;
		current->h = manhattan(current->x, current->y);
		current->g = 0;
		current->f = current->h + current->g;

		while (current->x != target->x || current->y != target->y) {
			int lowest = INT_MAX;
			int lowestIndex = -1;
			if (open.size() == 0)
				return nullptr;
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
				isFound = true;
				return target;
			}

			closed.push_back(current);
			std::vector<Cell*> neighborCells = grid->getAllNeighbors(current->x,
																	 current->y);
			std::vector<AStarNode*> neighbors;
			for (int i = 0; i < neighborCells.size(); i++) {
				if (!neighborCells[i]->isBlocked && !nodeExistsAtPosition(neighborCells[i]->x, neighborCells[i]->y))
					neighbors.push_back(createNode(*neighborCells[i]));
				if (neighborCells[i]->x == target->x && neighborCells[i]->y == target->y) {
					neighbors.push_back(target);
				}
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

	Cell* AStarPath::nextCell(Cell& _currentCell)
	{
		AStarNode* iterator = target;
		if (iterator->cell == &_currentCell)
			return iterator->cell;
		if (iterator->parent == nullptr)
			return nullptr;
		while (iterator->parent->cell != &_currentCell) {
			iterator = iterator->parent;
			if (iterator->parent == nullptr)
				return nullptr;
		}
		return iterator->cell;
	}

	void AStarPath::forget()
	{
		isFound = false;
		clear();
	}

	void AStarPath::clear()
	{
		isFound = false;
		start = nullptr;
		target = nullptr;
		current = nullptr;
		open.clear();
		closed.clear();
		nodes.clear();
	}

	bool AStarPath::isNodeInList(AStarNode* _node, std::vector<AStarNode*> _list)
	{
		for (int i = 0; i < _list.size(); i++) {
			if (_list[i] == _node)
				return true;
		}
		return false;
	}

	bool AStarPath::nodeExistsAtPosition(int _x, int _y)
	{
		for (auto& node : nodes) {
			if (node->x == _x && node->y == _y)
				return true;
		}
		return false;
	}

	AStarNode* AStarPath::createNode(Cell& _cell)
	{
		nodes.push_back(std::make_unique<AStarNode>(_cell));
		return nodes.back().get();
	}

	int AStarPath::manhattan(int _x, int _y)
	{
		return (abs(target->x - _x) + abs(target->y - _y)) * 10;
	}
}
