#include "Simulation.h"

Simulation::Simulation()
{
	srand(time(0));
	grid = std::make_unique<Grid>();
	path = std::make_unique<Path>(*grid, 0, 0, 5, 5);
	player = std::make_unique<Player>();
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
		player->grid = grid.get();
		path->find();
		hasStarted = true;
	}
	grid->update(_deltaTime);
	player->update(_deltaTime);
	input->update();
	return true;
}

void Simulation::draw(sf::RenderWindow& _window)
{
	grid->draw(_window);
}

void Simulation::setInput(InputManager& _input) {
	input = &_input;
	player->input = &_input;
}

