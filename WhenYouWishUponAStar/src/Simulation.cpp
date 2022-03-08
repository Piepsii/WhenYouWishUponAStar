#include "WhenYouWishUponAStar/Simulation.h"
#include "WhenYouWishUponAStar/CellObject.h"
#include "WhenYouWishUponAStar/Restable.h"
#include "WhenYouWishUponAStar/Starchaser.h"

namespace WhenYouWishUponAStar {

	Simulation::Simulation()
	{
		srand(time(0));
		grid = std::make_unique<Grid>();
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
			hasStarted = true;
			auto cellObject = spaceship.addComponent<CellObject>();
			cellObject->grid = grid.get();
			cellObject->start(3, 3);
			auto restable = spaceship.addComponent<Restable>();
			restable->start();
			auto path = starchaser.addComponent<Path>();
			auto starchaserComponent = starchaser.addComponent<Starchaser>();
		}
		grid->update(_deltaTime);
		player->update(_deltaTime);
		input->update();
		spaceship.update(_deltaTime);
		starchaser.update(_deltaTime);
		fallenStar.update(_deltaTime);
		tradingPost.update(_deltaTime);
		return true;
	}

	void Simulation::draw(sf::RenderWindow& _window)
	{
		grid->draw(_window);
		spaceship.draw(_window);
		starchaser.draw(_window);
		fallenStar.draw(_window);
		tradingPost.draw(_window);
	}

	void Simulation::setInput(InputManager& _input) {
		input = &_input;
		player->input = &_input;
	}
}
