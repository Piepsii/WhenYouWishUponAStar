#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>

#include "WhenYouWishUponAStar/Grid.h"
#include "WhenYouWishUponAStar/Path.h"
#include "WhenYouWishUponAStar/Player.h"
#include "WhenYouWishUponAStar/InputManager.h"

namespace WhenYouWishUponAStar {

	class Simulation
	{
	public:
		static Simulation* Instance();

		bool update(float deltaTime);
		void draw(sf::RenderWindow& _window);
		Simulation(Simulation& other) = delete;
		void operator=(const Simulation&) = delete;
		void setInput(InputManager& _input);

	protected:
		static Simulation* instance;

	private:
		Simulation();
		~Simulation();

		bool hasStarted = false;
		InputManager* input = nullptr;
		std::unique_ptr<Grid> grid = nullptr;
		std::unique_ptr<Player> player = nullptr;
		GameObject spaceship;
		GameObject tradingPost;
		GameObject fallenStar;
		GameObject starchaser;

		sf::Texture texture_spaceship;
		sf::Texture texture_tradingPost;
		sf::Texture texture_fallenStar;
		sf::Texture texture_starchaser;
	};
}
