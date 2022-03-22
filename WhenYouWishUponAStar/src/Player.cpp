#include "WhenYouWishUponAStar/Player.h"
#include "WhenYouWishUponAStar/StaticVariables.h"

namespace WhenYouWishUponAStar {

	Player::Player()
	{
	}

	void Player::update(float _deltaTime)
	{
		if (!isActive)
			return;
		handleInput();
		if (previousX != hoverX || previousY != hoverY) {
			if (selectedCell)
				selectedCell->isSelected = false;
			selectedCell = grid->getCell(hoverX, hoverY);
			selectedCell->isSelected = true;
		}
		previousX = hoverX;
		previousY = hoverY;
	}

	void Player::handleInput() {
		if (input->isKeyPressed(sf::Keyboard::Key::Up)) {
			hoverY--;
		}
		else if (input->isKeyPressed(sf::Keyboard::Key::Down)) {
			hoverY++;
		}
		else if (input->isKeyPressed(sf::Keyboard::Key::Left)) {
			hoverX--;
		}
		else if (input->isKeyPressed(sf::Keyboard::Key::Right)) {
			hoverX++;
		}
		else if (input->isKeyPressed(sf::Keyboard::Key::Enter)) {
			selectedCell->isBlocked = !selectedCell->isBlocked;
			hasUpdatedGrid = true;
		}
		else if (input->isKeyPressed(sf::Keyboard::Key::Space)) {
			needsPause = !needsPause;
		}
		else if (input->isKeyPressed(sf::Keyboard::Key::F)) {
			hasSelected = true;
			if (!isDragging) {
				selected.x = hoverX;
				selected.y = hoverY;
			}
		}
		else if (input->isKeyPressed(sf::Keyboard::Key::P)) {
			usesAStar = !usesAStar;
		}
		hoverX = std::clamp(hoverX, 0, COLUMNS - 1);
		hoverY = std::clamp(hoverY, 0, ROWS - 1);
	}
	sf::Vector2i Player::getHovered()
	{
		return sf::Vector2i(hoverX, hoverY);
	}
	sf::Vector2i Player::getSelected()
	{
		return selected;
	}
}
