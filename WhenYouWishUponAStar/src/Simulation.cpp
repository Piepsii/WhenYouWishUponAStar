// Simulation.cpp

#include "Simulation.h"

Simulation::Simulation(uint32_t _screenWidth,
					   uint32_t _screenHeight,
					   uint32_t _columns,
					   uint32_t _rows,
					   uint32_t _tileSize)
	: screenWidth(_screenWidth)
	, screenHeight(_screenHeight)
{
	srand(time(0));
}

Simulation::~Simulation()
{
}

bool Simulation::update(float deltaTime)
{
	return true;
}

void Simulation::draw(sf::RenderWindow& _window)
{
}
