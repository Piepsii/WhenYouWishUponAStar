#include "Node.h"

#include <random>

#include "Cell.h"

Node::Node()
{
	if (rand() % 100 < 20) {
		isBlocked = true;
	}
}

void Node::update(float _deltaTime)
{
}

void Node::draw(sf::RenderWindow& _window)
{
}
