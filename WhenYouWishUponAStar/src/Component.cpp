#include "WhenYouWishUponAStar/Component.h"

namespace WhenYouWishUponAStar {

	ComponentBase::ComponentBase(GameObject* _parent, const ComponentFamilyId _id)
		: parent(_parent)
		, id(_id) {

	}

	ComponentFamilyId ComponentBase::Id() const {
		return id;
	}

	void ComponentBase::update(float _deltaTime) {

	}

	void ComponentBase::draw(sf::RenderWindow& _window) {

	}
}
