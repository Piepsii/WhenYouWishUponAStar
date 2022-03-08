#pragma once

#include "WhenYouWishUponAStar/ComponentRegistry.h"
#include <SFML/Graphics.hpp>

namespace WhenYouWishUponAStar {

	class GameObject;

	class ComponentBase {
	public:
		ComponentBase(GameObject* parent, const ComponentFamilyId id);
		virtual ~ComponentBase() = default;

		ComponentFamilyId Id() const;

		virtual void update(float _deltaTime);
		virtual void draw(sf::RenderWindow& _window);

	protected:
		GameObject* parent;
		ComponentFamilyId id;
	};

	template<typename Derived>
	class Component : public ComponentBase {
	public:
		Component(GameObject* parent)
			: ComponentBase(parent, ComponentRegistry::family<Derived>) {

		}
	};
}
