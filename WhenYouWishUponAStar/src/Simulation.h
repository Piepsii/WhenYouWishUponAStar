#pragma once

#include <SFML/Graphics.hpp>
#include <random>

#include "Grid.h"
#include "Path.h"
#include "Player.h"
#include "InputManager.h"

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
	std::unique_ptr<Path> path = nullptr;
	std::unique_ptr<Player> player = nullptr;
};

