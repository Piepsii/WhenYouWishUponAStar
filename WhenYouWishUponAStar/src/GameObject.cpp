#include "WhenYouWishUponAStar/GameObject.h"
#include "WhenYouWishUponAStar/Component.h"

namespace WhenYouWishUponAStar {

	GameObject::GameObject()
		: isActive(true)
	{
	}

	GameObject::~GameObject() {
		for (auto& component : components) {
			delete component;
		}
	}

	void GameObject::update(float _deltaTime) {
		if (!isActive)
			return;

		for (auto& component : components) {
			component->update(_deltaTime);
		}
	}

	void GameObject::draw(sf::RenderWindow& _window)
	{
		if (!isActive)
			return;

		for (auto& component : components) {
			component->draw(_window);
		}
	}
}
