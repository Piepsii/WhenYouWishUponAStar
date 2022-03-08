#pragma once

#include <vector>
#include <type_traits>
#include <SFML/Graphics.hpp>
#include "WhenYouWishUponAStar/ComponentRegistry.h"

namespace WhenYouWishUponAStar {

	class ComponentBase;

	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		void update(float _deltaTime);
		void draw(sf::RenderWindow& _window);

		template<typename ComponentType>
		bool hasComponent() const {
			return get_component<ComponentType>() != nullptr;
		}

		template<typename ComponentType>
		ComponentType* addComponent() {
			static_assert(std::is_base_of<ComponentBase, ComponentType>::value,
						  "ComponentType must inherit from ComponentBase");
			ComponentType* component = new ComponentType(this, ComponentRegistry::family<ComponentType>());
			components.push_back(component);
			return component;
		}

		template <typename ComponentType>
		ComponentType* getComponent() {
			const ComponentFamilyId id = ComponentRegistry::family<ComponentType>();
			for (auto& component : components) {
				if (component->Id() == id) {
					return static_cast<ComponentType*>(component);
				}
			}
			return nullptr;
		}

		bool isActive;

	private:
		std::vector<ComponentBase*> components;
	};
}
