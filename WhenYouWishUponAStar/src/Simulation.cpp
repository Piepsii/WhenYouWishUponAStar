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
			hasStarted = true;

			if (!texture_spaceship.loadFromFile("assets/spaceship.png"))
				return -1;
			if (!texture_tradingPost.loadFromFile("assets/trading_post.png"))
				return -1;
			if (!texture_fallenStar.loadFromFile("assets/fallen_star.png"))
				return -1;
			if (!texture_starchaser.loadFromFile("assets/starchaser.png"))
				return -1;

			player->grid = grid.get();

			auto cellObject = spaceship.addComponent<CellObject>();
			cellObject->spawn(*grid.get());
			cellObject->setTexture(texture_spaceship);
			auto restable = spaceship.addComponent<Restable>();
			restable->start();

			cellObject = starchaser.addComponent<CellObject>();
			cellObject->spawn(*grid.get());
			cellObject->setTexture(texture_starchaser);
			auto path = starchaser.addComponent<AStarPath>();
			path->setGrid(*grid);
			path->find(0, 0, 5, 5);
			auto starchaserComponent = starchaser.addComponent<Starchaser>();

			cellObject = fallenStar.addComponent<CellObject>();
			cellObject->spawn(*grid.get());
			cellObject->setTexture(texture_fallenStar);

			cellObject = tradingPost.addComponent<CellObject>();
			cellObject->spawn(*grid.get());
			cellObject->setTexture(texture_tradingPost);
		}
		grid->update(_deltaTime);
		player->update(_deltaTime);
		if (player->hasUpdatedGrid) {
			player->hasUpdatedGrid = false;
			auto path = starchaser.getComponent<AStarPath>();
			path->forget();
			path->find(0, 0, 5, 5);
		}
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
