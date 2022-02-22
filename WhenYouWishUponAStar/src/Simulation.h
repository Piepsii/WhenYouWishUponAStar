#pragma once

#include <SFML/Graphics.hpp>
#include "Grid.h"
#include <random>

class Simulation
{
public:
	Simulation(uint32_t _screenWidth,
			   uint32_t _screenHeight,
			   uint32_t _columns,
			   uint32_t _rows,
			   uint32_t _tileSize);
	~Simulation();

	bool update(float deltaTime);
	void draw(sf::RenderWindow& _window);

private:
	uint32_t screenWidth, screenHeight;
};

