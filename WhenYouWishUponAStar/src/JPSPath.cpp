
#include "WhenYouWishUponAStar\JPSPath.h"

namespace WhenYouWishUponAStar {

	JPSPath::JPSPath(GameObject* _parent, const ComponentFamilyId _id)
		: ComponentBase(_parent, _id)
	{
		nodes.reserve(1000);
	}

	void JPSPath::draw(sf::RenderWindow& _window)
	{
		for (auto& n : nodes) {
			grid->drawPath(n.pos, colorNodes);
			if (n.parent != nullptr)
				grid->drawEdge(n.pos, n.parent->pos);
		}
		for (auto& pos : path) {
			grid->drawPath(pos, colorPath);
		}
	}

	void JPSPath::setGrid(Grid& _grid)
	{
		grid = &_grid;
	}

	bool JPSPath::find(int _sX, int _sY, int _tX, int _tY)
	{
		clear();
		start = sf::Vector2i(_sX, _sY);
		target = sf::Vector2i(_tX, _tY);
		current = start;
		createNode(start);

		while (containsOpenNodes()) 
		{
			int lowest = INT_MAX;
			int indexOfLowest = 0;
			for (int i = 0; i < nodes.size(); i++) 
			{
				if (nodes[i].closed)
					continue;
				if (nodes[i].f < lowest) 
				{
					lowest = nodes[i].f;
					indexOfLowest = i;
				}
			}
			current = nodes.at(indexOfLowest).pos;
			if (current == target) 
			{
				path = createPath();
				isFound = true;
				return true;
			}
			identifySuccessors(current);
		}
		isFound = false;
		return false;
	}

	void JPSPath::clear()
	{
		isFound = false;
		nodes.clear();
		path.clear();
	}

	void JPSPath::identifySuccessors(sf::Vector2i _current)
	{
		if (nodes.size() > 990)
			int i = 1;
		std::vector<sf::Vector2i> neighbors;
		neighbors = neighborsFromDirection(getNode(_current));

		for (auto& n : neighbors) {
			sf::Vector2i jumpPoint = jump(n, _current);
			if (jumpPoint != sf::Vector2i(-1, -1)) {
				for (auto& n : nodes) {
					if (n.closed) {
						if (getNode(jumpPoint) == &n)
							continue;
					}
				}
				int g = calcG(_current, jumpPoint, getNode(_current)->g);
				int h = manhattan(jumpPoint.x, jumpPoint.y);

				bool found = false;
				for (auto& n : nodes) {
					if (!n.closed && n.pos == jumpPoint) {
						found = true;
						if (g < n.g) {
							n.g = g;
							n.h = h;
							n.f = g + h;
							n.parent = getNode(_current);
						}
					}
				}
				if (!found) {
					JPSNode* n = createNode(jumpPoint);
					n->g = g;
					n->h = h;
					n->f = g + h;
					n->parent = getNode(_current);
				}
			}
		}
		getNode(_current)->closed = true;
	}

	sf::Vector2i JPSPath::jump(sf::Vector2i _this, sf::Vector2i _parent)
	{
		sf::Vector2i error = sf::Vector2i(-1, -1);
		sf::Vector2i _direction = _this - _parent;
		if (grid->isBlockedAt(_this))
			return error;

		if (_this == target) {
			return _this;
		}

		// Diagonal Case
		if (_direction.x != 0 && _direction.y != 0) {
			sf::Vector2i offsetX = sf::Vector2i(-_direction.x, 0);
			sf::Vector2i offsetY = sf::Vector2i(0, -_direction.y);
			if (forcedNeighborCheck(_this, _direction, offsetX) ||
				forcedNeighborCheck(_this, _direction, offsetY))
			{
				return _this;
			}
			sf::Vector2i directionX = sf::Vector2i(_this.x + _direction.x, _this.y);
			sf::Vector2i directionY = sf::Vector2i(_this.x, _this.y + _direction.y);
			if (jump(directionX, _this) != error ||
				jump(directionY, _this) != error) {
				return _this;
			}
		}
		else{
			if (_direction.x != 0) {
				// Horizontal Case
				sf::Vector2i offsetPos = sf::Vector2i(0, 1);
				sf::Vector2i offsetNeg = sf::Vector2i(0, -1);
				if (forcedNeighborCheck(_this, _direction, offsetPos) ||
					forcedNeighborCheck(_this, _direction, offsetNeg))
					return _this;
				}
			else {
				// Vertical Case
				sf::Vector2i offsetPos = sf::Vector2i(1, 0);
				sf::Vector2i offsetNeg = sf::Vector2i(-1, 0);
				if (forcedNeighborCheck(_this, _direction, offsetPos) ||
					forcedNeighborCheck(_this, _direction, offsetNeg))
					return _this;

			}
		}
		return jump(_this + _direction, _this);
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

	bool JPSPath::forcedNeighborCheck(sf::Vector2i _this, sf::Vector2i _direction, sf::Vector2i _offset)
	{
		if (!grid->isBlockedAt(_this + _direction + _offset)
			&& grid->isBlockedAt(_this + _offset)) { 
			return true;
		}
		return false;
	}

	std::vector<sf::Vector2i> JPSPath::neighborsFromDirection(JPSNode* _node)
	{
		JPSNode* parent = _node->parent;
		std::vector<sf::Vector2i> result;
		sf::Vector2i nodePos = _node->pos;
		int x = nodePos.x;
		int y = nodePos.y;

		if (parent != nullptr) {
			sf::Vector2i parentPos = parent->pos;
			int px = parentPos.x;
			int py = parentPos.y;
			int dx = std::clamp((x - px), -1, 1);
			int dy = std::clamp((y - py), -1, 1);

			if (dx != 0 && dy != 0) {
				if (grid->isWalkableAt(x, y + dy))
					result.push_back(sf::Vector2i(x, y + dy));
				if (grid->isWalkableAt(x + dx, y))
					result.push_back(sf::Vector2i(x + dx, y));
				if (grid->isWalkableAt(x + dx, y + dy))
					result.push_back(sf::Vector2i(x + dx, y + dy));
				if (grid->isBlockedAt(x - dx, y))
					result.push_back(sf::Vector2i(x - dx, y + dy));
				if (grid->isBlockedAt(x, y - dy))
					result.push_back(sf::Vector2i(x + dx, y - dy));
				
			}
			else {
				if (dx == 0) {
					if (grid->isWalkableAt(x, y + dy))
						result.push_back(sf::Vector2i(x, y + dy));
					if (grid->isBlockedAt(x + 1, y))
						result.push_back(sf::Vector2i(x + 1, y + dy));
					if (grid->isBlockedAt(x - 1, y))
						result.push_back(sf::Vector2i(x - 1, y + dy));
				}
				else {
					if (grid->isWalkableAt(x + dx, y))
						result.push_back(sf::Vector2i(x + dx, y));
					if (grid->isBlockedAt(x, y + 1))
						result.push_back(sf::Vector2i(x + dx, y + 1));
					if (grid->isBlockedAt(x, y - 1))
						result.push_back(sf::Vector2i(x + dx, y - 1));
				}
			}
		}
		else {
			result.push_back(sf::Vector2i(x - 1, y));
			result.push_back(sf::Vector2i(x, y - 1));
			result.push_back(sf::Vector2i(x + 1, y));
			result.push_back(sf::Vector2i(x, y + 1));
			result.push_back(sf::Vector2i(x - 1, y - 1));
			result.push_back(sf::Vector2i(x + 1, y - 1));
			result.push_back(sf::Vector2i(x - 1, y + 1));
			result.push_back(sf::Vector2i(x + 1, y + 1));
		}
		return result;
	}

	int JPSPath::calcG(sf::Vector2i _current, sf::Vector2i _new, int _g)
	{
		if (_current == _new)
			return _g;
		if (_current.x == _new.x || _current.y == _new.y) {
			_current.x += std::clamp(_new.x - _current.x, -1, 1);
			_current.y += std::clamp(_new.y - _current.y, -1, 1);
			_g = calcG(_current, _new, _g + 10);
		}
		else {
			_current.x += std::clamp(_new.x - _current.x, -1, 1);
			_current.y += std::clamp(_new.y - _current.y, -1, 1);
			_g = calcG(_current, _new, _g + 14);
		}
		return _g;
	}

	bool JPSPath::containsOpenNodes()
	{
		for (auto& n : nodes) {
			if (!n.closed) {
				return true;
			}
		}
		return false;
	}

	std::vector<sf::Vector2i> JPSPath::createPath()
	{
		std::vector<sf::Vector2i> result;
		JPSNode* current = getNode(target);
		result.push_back(current->pos);
		while (current->parent != nullptr) {
			sf::Vector2i distance = current->parent->pos - current->pos;
			distance.x = std::clamp(distance.x, -1, 1);
			distance.y = std::clamp(distance.y, -1, 1);
			sf::Vector2i currentPos = current->pos;
			while (currentPos != current->parent->pos) {
				currentPos += distance;
				result.push_back(currentPos);
			}
			current = current->parent;
		}
		std::reverse(result.begin(), result.end());
		return result;
	}

	sf::Vector2i JPSPath::nextPosition(sf::Vector2i _current)
	{
		if (target == _current)
			return target;

		for (int i = 0; i < path.size(); i++) {
			if (path[i] == _current)
				return path[i + 1];
		}
		return sf::Vector2i(-1, -1);
	}

	void JPSPath::forget()
	{
		isFound = false;
		clear();
	}
	 
	int JPSPath::manhattan(int _x, int _y)
	{
		return (abs(target.x - _x) + abs(target.y - _y)) * 10;
	}

}
