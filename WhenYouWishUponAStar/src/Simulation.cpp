#include "WhenYouWishUponAStar/Simulation.h"
#include "WhenYouWishUponAStar/CellObject.h"
#include "WhenYouWishUponAStar/Restable.h"
#include "WhenYouWishUponAStar/Starchaser.h"
#include "WhenYouWishUponAStar/JPSPath.h"

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

			auto spaceshipObject = spaceship.addComponent<CellObject>();
			spaceshipObject->spawn(*grid.get());
			spaceshipObject->setTexture(texture_spaceship);
			auto restable = spaceship.addComponent<Restable>();
			restable->start();

			auto fallenStarObject = fallenStar.addComponent<CellObject>();
			fallenStarObject->spawn(*grid.get());
			fallenStarObject->setTexture(texture_fallenStar);

			auto tradingPostObject = tradingPost.addComponent<CellObject>();
			tradingPostObject->spawn(*grid.get());
			tradingPostObject->setTexture(texture_tradingPost);

			auto starchaserObject = starchaser.addComponent<CellObject>();
			starchaserObject->spawn(*grid.get());
			starchaserObject->setTexture(texture_starchaser);
			auto path = starchaser.addComponent<AStarPath>();
			path->setGrid(*grid);
			auto jpsPath = starchaser.addComponent<JPSPath>();
			jpsPath->setGrid(*grid);
			auto starchaserComponent = starchaser.addComponent<Starchaser>();
			starchaserComponent->sense(*starchaserObject,
									   *fallenStarObject,
									   *spaceshipObject,
									   *tradingPostObject,
									   *path,
									   *jpsPath);
		}
		grid->update(_deltaTime);
		player->update(_deltaTime);
		if (player->hasUpdatedGrid) {
			player->hasUpdatedGrid = false;
			auto path = starchaser.getComponent<AStarPath>();
			path->isFound = false;
			auto jpsPath = starchaser.getComponent<JPSPath>();
			jpsPath->isFound = false;
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
