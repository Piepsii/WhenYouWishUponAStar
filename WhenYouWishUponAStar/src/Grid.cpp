#include "WhenYouWishUponAStar/Grid.h"
#include "WhenYouWishUponAStar/StaticVariables.h"

namespace WhenYouWishUponAStar {

	Grid::Grid()
	{
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				cells[j * columns + i] = std::make_unique<Cell>(i, j);
			}
		}

		for (int i = 0; i < columns - 1; i++) {
			for (int j = 0; j < rows - 1; j++) {
			}
		}
	}

	void Grid::update(float _deltaTime)
	{
		if (!isActive)
			return;

		for (int i = 0; i < size; i++) {
			cells[i]->update(_deltaTime);
		}
	}

	void Grid::draw(sf::RenderWindow& _window)
	{
		if (!isActive)
			return;

		for (int i = 0; i < size; i++) {
			cells[i]->draw(_window);
		}
		for (auto& e : edges)
			_window.draw(e);
		edges.clear();
	}

	void Grid::drawPath(sf::Vector2i _pos, sf::Color _color)
	{
		getCell(_pos)->pathColor = _color;
		getCell(_pos)->drawPath = true;
	}

	void Grid::drawEdge(sf::Vector2i _start, sf::Vector2i _end)
	{
		sf::Vector2f pos = getCell(_start)->drawPos;
		sf::Vector2f length = getCell(_end)->drawPos - getCell(_start)->drawPos;
		float magnitude = sqrtf(length.x * length.x + length.y * length.y);
		sf::Vector2f size = sf::Vector2f(magnitude, 6.0f);
		float angle = atan2(length.y, length.x);
		float angleInDegree = angle * 180.0f / 3.14159265358979323846f;

		sf::RectangleShape edge = sf::RectangleShape(size);
		edge.setOrigin(0.0f, 6.0f / 2.0f);
		edge.setRotation(angleInDegree);
		edge.setPosition(pos);
		edge.setFillColor(sf::Color::Green);
		edges.push_back(edge);
	}

	uint32_t Grid::Columns()
	{
		return columns;
	}

	uint32_t Grid::Rows()
	{
		return rows;
	}

	uint32_t Grid::Size()
	{
		return columns * rows;
	}

	sf::Vector2i Grid::GetRandomNeighbor(sf::Vector2i _pos)
	{
		int neighborX = -1, neighborY = -1;
		while (neighborX < 0 || neighborX >= columns) {
			int offsetX = rand() % 3 - 1;
			neighborX = _pos.x + offsetX;
		}
		while (neighborY < 0 || neighborY >= rows) {
			int offsetY = rand() % 3 - 1;
			neighborY = _pos.y + offsetY;
		}
		sf::Vector2i result = { neighborX, neighborY };
		return result;
	}

	uint32_t Grid::GetRandomNeighborAsIndex(sf::Vector2i _pos)
	{
		int neighborX = -1, neighborY = -1;
		while (neighborX < 0 || neighborX >= columns) {
			int offsetX = rand() % 3 - 1;
			neighborX = _pos.x + offsetX;
		}
		while (neighborY < 0 || neighborY >= rows) {
			int offsetY = rand() % 3 - 1;
			neighborY = _pos.y + offsetY;
		}

		uint32_t index = neighborY * columns + neighborX;
		return index;
	}

	Cell* Grid::getRandomCell(bool _includeBlocked)
	{
		bool isBlocked = true;
		Cell* result;
		do {
			int index = rand() % size;
			result = getCell(index);
			isBlocked = result->isBlocked;
			if (_includeBlocked)
				isBlocked = false;
		} while (isBlocked);
		return result;
	}

	Cell* Grid::getCell(int _x, int _y)
	{
		if (_x < 0 || _x >= columns ||
			_y < 0 || _y >= rows)
			return nullptr;

		uint32_t index = _y * columns + _x;
		return cells[index].get();
	}

	Cell* Grid::getCell(int _index)
	{
		return cells[_index].get();
	}

	Cell* Grid::getCell(sf::Vector2i _pos)
	{
		if (_pos.x < 0 || _pos.x >= columns ||
			_pos.y < 0 || _pos.y >= rows)
			return nullptr;

		uint32_t index = _pos.y * columns + _pos.x;
		return cells[index].get();
	}

	bool Grid::isBlockedAt(int _x, int _y)
	{
		if (_x < 0 || _y < 0 || _x > columns - 1 || _y > rows - 1)
			return true;
		return getCell(_x, _y)->isBlocked;
	}

	bool Grid::isBlockedAt(sf::Vector2i _pos)
	{
		if(_pos.x < 0 || _pos.y < 0 || _pos.x > columns - 1 || _pos.y > rows - 1)
			return true;
		return getCell(_pos.x, _pos.y)->isBlocked;
	}

	std::vector<Cell*> Grid::getAllNeighbors(int _x, int _y)
	{
		std::vector<Cell*> result;
		result.push_back(getCell(_x - 1, _y));
		result.push_back(getCell(_x, _y - 1));
		result.push_back(getCell(_x + 1, _y));
		result.push_back(getCell(_x, _y + 1));

		if (result[0] != nullptr && result[1] != nullptr) {
			if (!result[0]->isBlocked && !result[1]->isBlocked)
				result.push_back(getCell(_x - 1, _y - 1));
		}
		if (result[1] != nullptr && result[2] != nullptr) {
			if (!result[1]->isBlocked && !result[2]->isBlocked)
				result.push_back(getCell(_x + 1, _y - 1));
		}
		if (result[2] != nullptr && result[3] != nullptr) {
			if (!result[2]->isBlocked && !result[3]->isBlocked)
				result.push_back(getCell(_x - 1, _y + 1));
		}
		if (result[3] != nullptr && result[0] != nullptr) {
			if (!result[3]->isBlocked && !result[0]->isBlocked)
				result.push_back(getCell(_x + 1, _y + 1));
		}

		std::vector<int> indeces;
		for (int i = 0; i < result.size(); i++) {
			if (result[i] == nullptr)
				indeces.push_back(i);
		}
		std::sort(indeces.begin(), indeces.end());
		for (int i = indeces.size() - 1; i >= 0; i--) {
			result.erase(result.begin() + indeces[i]);
		}
		return result;
	}
}
