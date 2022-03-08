#include "WhenYouWishUponAStar/CellObject.h"

namespace WhenYouWishUponAStar {

	CellObject::CellObject(GameObject* _parent, const ComponentFamilyId _id)
		: ComponentBase(_parent, _id)
	{
	}

	CellObject::~CellObject()
	{

	}

	void CellObject::spawn() {
		cell = grid->getRandomCell();
		x = cell->x;
		y = cell->y;
	}

	void CellObject::spawn(int _x, int _y)
	{
		x = _x;
		y = _y;
		cell = grid->getCell(x, y);
	}

	void CellObject::update(float _deltaTime)
	{
	}
}
