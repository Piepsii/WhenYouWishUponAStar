
#include "WhenYouWishUponAStar\JPSPath.h"

namespace WhenYouWishUponAStar {

	JPSPath::JPSPath(GameObject* _parent, const ComponentFamilyId _id)
		: ComponentBase(_parent, _id)
	{
		nodes.reserve(200);
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
		open.push_back(createNode(start));

		while (!open.empty()) 
		{
			int lowest = INT_MAX;
			int indexOfLowest = -1;
			if (open.size() == 0)
				return std::vector<sf::Vector2i>();
			for (int i = 0; i < open.size(); i++) 
			{
				if (open[i]->closed)
					continue;
				if (open[i]->f < lowest) 
				{
					lowest = open[i]->f;
					indexOfLowest = i;
				}
			}
			current = open.at(indexOfLowest)->pos;
			if (current == target) 
			{
				// to-do: create vector of positions
		return std::vector<sf::Vector2i>();
			}
			if (current == start) {
				identifySuccessors(current, true);
			}
			identifySuccessors(current);
		}
	}

	void JPSPath::identifySuccessors(sf::Vector2i _current, bool _first)
	{
		std::vector<sf::Vector2i> neighbors;
		if (_first) {
			neighbors.push_back(sf::Vector2i(-1, -1));
			neighbors.push_back(sf::Vector2i( 0, -1));
			neighbors.push_back(sf::Vector2i( 1, -1));

			neighbors.push_back(sf::Vector2i(-1,  0));
			neighbors.push_back(sf::Vector2i( 1,  0));
			
			neighbors.push_back(sf::Vector2i(-1,  1));
			neighbors.push_back(sf::Vector2i( 0,  1));
			neighbors.push_back(sf::Vector2i( 1,  1));
		}
		else {
			sf::Vector2i parentPos = getNode(_current)->parent->pos;
			sf::Vector2i direction = _current - parentPos;
			neighbors = neighborsFromDirection(direction);
		}

		for (auto& n : neighbors) {
			jump(current, n);
		}
		getNode(_current)->closed = true;
	}

	JPSNode* JPSPath::jump(sf::Vector2i _this, sf::Vector2i _direction)
	{
		if (grid->isBlockedAt(_this))
			return nullptr;

		sf::Vector2i next = _this + _direction;
		if (next == target)
			return createNode(next);

		// Diagonal Case
		if (_direction.x != 0 && _direction.y != 0) {
			JPSNode* forcedNeighborNodeH = jump(next, sf::Vector2i(_direction.x, 0));
			if (forcedNeighborNodeH != nullptr) {
				JPSNode* secondary = createNode(_this);
				forcedNeighborNodeH->parent = secondary;
				JPSNode* currentNode = getNode(current);
				secondary->parent = currentNode;
				return forcedNeighborNodeH;
			}
			JPSNode* forcedNeighborNodeV = jump(next, sf::Vector2i(0, _direction.y));
			if (forcedNeighborNodeV != nullptr) {
				JPSNode* secondary = createNode(_this);
				forcedNeighborNodeV->parent = secondary;
				JPSNode* currentNode = getNode(current);
				secondary->parent = currentNode;
				return forcedNeighborNodeV;
			}
		}
		// Horizontal Case
		if (_direction.x != 0 && _direction.y == 0) {
			sf::Vector2i offsetPos = sf::Vector2i(0, 1);
			JPSNode* jumpPoint = forcedNeighborCheck(_this, _direction, offsetPos);
			if (jumpPoint != nullptr)
				return jumpPoint;
			sf::Vector2i offsetNeg = sf::Vector2i(0, -1);
			jumpPoint = forcedNeighborCheck(_this, _direction, offsetNeg);
			if (jumpPoint != nullptr)
				return jumpPoint;
		}
		// Vertical Case
		if(_direction.x == 0 && _direction.y != 0) {
			sf::Vector2i offsetPos = sf::Vector2i(1, 0);
			JPSNode* jumpPoint = forcedNeighborCheck(_this, _direction, offsetPos);
			if (jumpPoint != nullptr)
				return jumpPoint;

			sf::Vector2i offsetNeg = sf::Vector2i(-1, 0);
			jumpPoint = forcedNeighborCheck(_this, _direction, offsetNeg);
			if (jumpPoint != nullptr)
				return jumpPoint;
		}
		
		return jump(next, _direction);
	}

	JPSNode* JPSPath::getNode(sf::Vector2i _pos)
	{
		for (auto& n : nodes) {
			if (n.pos == _pos)
				return &n;
		}
		return nullptr;
	}

	JPSNode* JPSPath::createNode(sf::Vector2i _pos)
	{
		if (getNode(_pos) != nullptr) {
			return getNode(_pos);
		}
		nodes.push_back(JPSNode(_pos));
		return &nodes.back();
	}

	JPSNode* JPSPath::forcedNeighborCheck(sf::Vector2i _this, sf::Vector2i _direction, sf::Vector2i _offset)
	{
		if (grid->isBlockedAt(_this + _offset)) {
			auto forcedNeighbor = _this + _direction + _offset;
			if (!grid->isBlockedAt(forcedNeighbor)) {
				JPSNode* secondary = createNode(_this);
				JPSNode* forcedNeighborNode = createNode(forcedNeighbor);
				open.push_back(forcedNeighborNode);
				forcedNeighborNode->parent = secondary;
				JPSNode* currentNode = getNode(current);
				secondary->parent = currentNode;
				return secondary;
			}
		}
		return nullptr;
	}

	std::vector<sf::Vector2i> JPSPath::neighborsFromDirection(sf::Vector2i _direction)
	{
		std::vector<sf::Vector2i> result;
		if (_direction.x == 0 && _direction.y == 0)
			return result;

		sf::Vector2i unitDirection;
		unitDirection.x = _direction.x != 0 ? _direction.x / abs(_direction.x) : 0;
		unitDirection.y = _direction.y != 0 ? _direction.y / abs(_direction.y) : 0;
		result.push_back(unitDirection);

		if (unitDirection.x == 0) {
			unitDirection.x = 1;
			result.push_back(unitDirection);
			unitDirection.x = -1;
			result.push_back(unitDirection);
			return result;
		}
		if (unitDirection.y == 0) {
			unitDirection.y = 1;
			result.push_back(unitDirection);
			unitDirection.y = -1;
			result.push_back(unitDirection);
			return result;
		}
		int x = unitDirection.x;
		unitDirection.x = 0;
		result.push_back(unitDirection);
		unitDirection.x = x;
		unitDirection.y = 0;
		result.push_back(unitDirection);
		return result;
	}

	sf::Vector2i JPSPath::nextPosition(sf::Vector2i _current)
	{
		return sf::Vector2i();
	}

	int JPSPath::manhattan(int _x, int _y)
	{
		return (abs(target.x - _x) + abs(target.y - _y)) * 10;
	}

}
