#pragma once

#include <SFML/Graphics.hpp>
#include <random>

#include "Grid.h"

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

	Grid* grid;
};

