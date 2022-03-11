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

		void spawn(Grid& _grid);
		void spawn(Grid& _grid, int _x, int _y);
		void update(float _deltaTime);
		void draw(sf::RenderWindow& _window);
		void setTexture(sf::Texture& _texture);

		int x = 0;
		int y = 0;
		Cell* cell = nullptr;
		Grid* grid = nullptr;

	private:
		sf::Sprite sprite;
	};

}
