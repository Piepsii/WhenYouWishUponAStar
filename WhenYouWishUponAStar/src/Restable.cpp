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
		float radius = cell->width / 3;
		shape = sf::CircleShape(radius);
		shape.setFillColor(sf::Color::Magenta);
		shape.setOrigin(radius,
						radius);
		shape.setPosition(cellObject->x * cell->width + cell->width / 2,
						  cellObject->y * cell->height + cell->height / 2);
	}
	void Restable::update(float _deltaTime)
	{
		auto cellObject = parent->getComponent<CellObject>();
		auto cell = cellObject->cell;
		shape.setPosition(cellObject->x * cell->width + cell->width / 2,
						  cellObject->y * cell->height + cell->height / 2);
	}

	void Restable::draw(sf::RenderWindow& _window)
	{
		_window.draw(shape);
	}
}
