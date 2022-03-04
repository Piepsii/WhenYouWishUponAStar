#pragma once

#include <SFML/Graphics.hpp>
#include <random>

#include "Grid.h"
#include "Path.h"

class Simulation
{
public:
	static Simulation* Instance();
	
	bool update(float deltaTime);
	void draw(sf::RenderWindow& _window);
	Simulation(Simulation& other) = delete;
	void operator=(const Simulation&) = delete;

protected:
	static Simulation* instance;

private:
	Simulation();
	~Simulation();

	bool hasStarted = false;
	std::unique_ptr<Grid> grid = nullptr;
	std::unique_ptr<Path> path = nullptr;
};

