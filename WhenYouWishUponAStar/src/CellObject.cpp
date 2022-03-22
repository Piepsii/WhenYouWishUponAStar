#include "WhenYouWishUponAStar/CellObject.h"

namespace WhenYouWishUponAStar {

	CellObject::CellObject(GameObject* _parent, const ComponentFamilyId _id)
		: ComponentBase(_parent, _id)
	{
	}

	CellObject::~CellObject()
	{

	}

	void CellObject::spawn(Grid& _grid) {
		grid = &_grid;
		cell = grid->getRandomCell();
		x = cell->x;
		y = cell->y;
		sprite.setPosition(cell->x * cell->width, cell->y * cell->height);
	}

	void CellObject::spawn(Grid& _grid, int _x, int _y)
	{
		grid = &_grid;
		x = _x;
		y = _y;
		cell = grid->getCell(x, y);
		sprite.setPosition(cell->x * cell->width, cell->y * cell->height);
	}

	void CellObject::respawn()
	{
		cell = grid->getRandomCell();
		x = cell->x;
		y = cell->y;
		sprite.setPosition(cell->x * cell->width, cell->y * cell->height);
	}

	void CellObject::update(float _deltaTime)
	{
		cell = grid->getCell(x, y);
	}
	void CellObject::draw(sf::RenderWindow& _window)
	{
		_window.draw(sprite);
	}
	void CellObject::setTexture(sf::Texture& _texture)
	{
		sprite.setTexture(_texture);
		sprite.setPosition(cell->x * cell->width, cell->y * cell->height);
		sprite.setScale(cell->width / _texture.getSize().x, cell->height / _texture.getSize().y);
	}
	void CellObject::move()
	{
		sprite.setPosition(cell->x * cell->width, cell->y * cell->height);
	}

	void CellObject::moveTo(Cell& _cell)
	{
		if (&_cell == nullptr)
			return;
		cell = &_cell;
		sprite.setPosition(cell->x * cell->width, cell->y * cell->height);
	}
	void CellObject::setRotation(float _angle)
	{
		sprite.setRotation(_angle);
	}
}
