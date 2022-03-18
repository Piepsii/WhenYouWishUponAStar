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

	bool Grid::isBlockedAt(sf::Vector2i _pos)
	{
		if(_pos.x < 0 || _pos.y < 0 || _pos.x > columns || _pos.y > rows)
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
