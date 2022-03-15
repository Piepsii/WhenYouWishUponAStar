#include "WhenYouWishUponAStar/Restable.h"
#include "WhenYouWishUponAStar/CellObject.h"
#include "WhenYouWishUponAStar/Cell.h"

namespace WhenYouWishUponAStar {

	Restable::Restable(GameObject* _parent, const ComponentFamilyId _id)
		: ComponentBase(_parent, _id)
	{
	}

	Restable::~Restable()
	{
	}
	void Restable::start()
	{
		auto cellObject = parent->getComponent<CellObject>();
		auto cell = cellObject->cell;
	}
	void Restable::update(float _deltaTime)
	{
		auto cellObject = parent->getComponent<CellObject>();
		auto cell = cellObject->cell;
	}

	void Restable::draw(sf::RenderWindow& _window)
	{
	}
}
