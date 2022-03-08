#pragma once

#include "WhenYouWishUponAStar/Component.h"
#include "WhenYouWishUponAStar/Cell.h"
#include "WhenYouWishUponAStar/Grid.h"


namespace WhenYouWishUponAStar {

	class CellObject
		: public ComponentBase
	{
	public:
		CellObject(GameObject* _parent, const ComponentFamilyId _id);
		~CellObject();

		void spawn();
		void spawn(int _x, int _y);
		void update(float _deltaTime);

		int x = 0;
		int y = 0;
		Cell* cell = nullptr;
		Grid* grid = nullptr;

	private:

	};

}
