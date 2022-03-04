// Simulation.cpp

#include "Simulation.h"

Simulation::Simulation()
{
	srand(time(0));
	grid = std::make_unique<Grid>();
	path = std::make_unique<Path>(*grid, 0, 0, 5, 5);
}

Simulation::~Simulation()
{
	delete instance;
	instance = nullptr;
}

Simulation* Simulation::instance = nullptr;

Simulation* Simulation::Instance()
{
	if (instance == nullptr) {
		instance = new Simulation();
	}
	return instance;
}

bool Simulation::update(float _deltaTime)
{
	if (!hasStarted) {
		path->find();
		hasStarted = true;
	}
	grid->update(_deltaTime);
	return true;
}

void Simulation::draw(sf::RenderWindow& _window)
{
	grid->draw(_window);
}