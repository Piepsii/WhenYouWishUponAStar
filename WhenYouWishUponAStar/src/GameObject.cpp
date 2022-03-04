#include "GameObject.h"

GameObject::GameObject()
	: isActive(true)
{
}

void GameObject::draw(sf::RenderWindow& _window)
{
	if (!isActive)
		return;
}
