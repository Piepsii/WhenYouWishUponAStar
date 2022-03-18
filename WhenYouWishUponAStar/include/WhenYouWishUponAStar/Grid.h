#pragma once

#include <array>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "WhenYouWishUponAStar/GameObject.h"
#include "WhenYouWishUponAStar/AStarNode.h"
#include "WhenYouWishUponAStar/Cell.h"
#include "WhenYouWishUponAStar/StaticVariables.h"

namespace WhenYouWishUponAStar {

	class Grid : public GameObject
	{
	public:
		Grid();
		void update(float _deltaTime);
		void draw(sf::RenderWindow& _window);
		uint32_t Columns();
		uint32_t Rows();
		uint32_t Size();
		sf::Vector2i GetRandomNeighbor(sf::Vector2i _pos);
		uint32_t GetRandomNeighborAsIndex(sf::Vector2i _pos);
		Cell* getRandomCell(bool _includeBlocked = false);
		Cell* getCell(int _x, int _y);
		Cell* getCell(int _index);
		bool isBlockedAt(sf::Vector2i _pos);
		std::vector<Cell*> getAllNeighbors(int _x, int _y);

	private:
		const static uint32_t columns = COLUMNS;
		const static uint32_t rows = ROWS;
		const static uint32_t size = columns * rows;
		const static uint32_t edgeAmount = 2 * size - columns - rows;
		std::unique_ptr<Cell> cells[size];

		sf::RectangleShape edges[edgeAmount];
	};
}
