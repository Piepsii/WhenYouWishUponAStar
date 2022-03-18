
#include "WhenYouWishUponAStar\JPSPath.h"

namespace WhenYouWishUponAStar {

	JPSPath::JPSPath(GameObject* _parent, const ComponentFamilyId _id)
		: ComponentBase(_parent, _id)
	{
	}

	void JPSPath::setGrid(Grid& _grid)
	{
		grid = &_grid;
	}

	std::vector<sf::Vector2i> JPSPath::find(int _sX, int _sY, int _tX, int _tY)
	{
		start = sf::Vector2i(_sX, _sY);
		target = sf::Vector2i(_tX, _tY);
		current = start;
		open.push_back(JPSNode(start));

		while (!open.empty()) {
			// open.findBestF()
			int lowest = INT_MAX;
			int indexOfLowest = -1;
			if (open.size() == 0)
				return std::vector<sf::Vector2i>();
			for (int i = 0; i < open.size(); i++) {
				if (open[i].f < lowest) {
					lowest = open[i].f;
					indexOfLowest = i;
				}
			}
			current = open.at(indexOfLowest).pos;
			open.erase(open.begin() + indexOfLowest);

			if (current == target) {
				// to-do: create vector of positions
				return std::vector<sf::Vector2i>();
			}

			identifySuccessors(current);
		}
	}

	void JPSPath::identifySuccessors(sf::Vector2i _current)
	{
		sf::Vector2i parentPos = getNode(_current)->parent->pos;
		sf::Vector2i direction = _current - parentPos;

		// get neighbors from direction
		// getNeighbors(direction)
		std::vector<sf::Vector2i> neighbors;
		for (auto& n : neighbors) {
			jump(current, n);
		}
		getNode(_current)->closed = true;
	}

	JPSNode* JPSPath::jump(sf::Vector2i _this, sf::Vector2i _direction)
	{
		if (grid->isBlockedAt(_this + _direction))
			return nullptr;

		sf::Vector2i next = _this + _direction;

		// Diagonal Case
		if (_direction.x != 0 && _direction.y != 0) {
			if (/* diagonal forced neighbor check*/false) {
				return &createNode(next);
			}

			if (jump(next, sf::Vector2i(_direction.x, 0)) ||
				jump(next, sf::Vector2i(0, _direction.y))) {

			}
		}
		else {
			// Horizontal Case
			if (_direction.x != 0) {
				auto offsetPos = sf::Vector2i(0, 1);
				forcedNeighborCheck(_this, _direction, offsetPos);
				auto offsetNeg = sf::Vector2i(0, -1);
				forcedNeighborCheck(_this, _direction, offsetNeg);
			}
			//Vertical Case
			else {
				auto offsetPos = sf::Vector2i(1, 0);
				forcedNeighborCheck(_this, _direction, offsetPos);
				auto offsetNeg = sf::Vector2i(-1, 0);
				forcedNeighborCheck(_this, _direction, offsetNeg);
			}
		}

		return jump(next, _direction);
	}

	JPSNode* JPSPath::getNode(sf::Vector2i _pos)
	{
		for (auto& n : open) {
			if (n.pos == _pos)
				return &n;
		}
		return nullptr;
	}

	JPSNode JPSPath::createNode(sf::Vector2i _pos)
	{
		if (getNode(_pos)) {
			return *getNode(_pos);
		}
		nodes.push_back(JPSNode(_pos));
		return nodes.back();
	}

	bool JPSPath::forcedNeighborCheck(sf::Vector2i _this, sf::Vector2i _direction, sf::Vector2i _offset)
	{
		if (grid->isBlockedAt(_this + _offset)) {
			auto forcedNeighbor = _this + _direction + _offset;
			if (!grid->isBlockedAt(forcedNeighbor)) {
				JPSNode* secondary = &createNode(_this);
				JPSNode* forcedNeighborNode = &createNode(forcedNeighbor);
				open.push_back(*forcedNeighborNode);
				forcedNeighborNode->parent = secondary;
				JPSNode* currentNode = getNode(current);
				secondary->parent = currentNode;
			}
		}
	}

	sf::Vector2i JPSPath::nextPosition(sf::Vector2i _current)
	{
		return sf::Vector2i();
	}

	int JPSPath::manhattan(int _x, int _y)
	{
		return abs(target.x - _x) + abs(target.y - _y) * 10;
	}

}
