// Simulation.cpp

#include "Simulation.h"

Simulation::Simulation()
{
	srand(time(0));
	grid = new Grid();
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
	grid->update(_deltaTime);
	return true;
}

void Simulation::draw(sf::RenderWindow& _window)
{
	grid->draw(_window);
}