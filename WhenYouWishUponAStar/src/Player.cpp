#include "Player.h"
#include "StaticVariables.h"

Player::Player()
{
}

void Player::update(float _deltaTime)
{
	if (!isActive)
		return;
	handleInput();
	if (previousX != selectX || previousY != selectY) {
		if(selectedCell)
			selectedCell->isSelected = false;
		selectedCell = grid->getCell(selectX, selectY);
		selectedCell->isSelected = true;
	}
	previousX = selectX;
	previousY = selectY;
}

void Player::handleInput() {
	if (input->isKeyPressed(sf::Keyboard::Key::Up)) {
		selectY--;
	}
	else if (input->isKeyPressed(sf::Keyboard::Key::Down)) {
		selectY++;
	}
	else if (input->isKeyPressed(sf::Keyboard::Key::Left)) {
		selectX--;
	}
	else if (input->isKeyPressed(sf::Keyboard::Key::Right)) {
		selectX++;
	}
	else if (input->isKeyPressed(sf::Keyboard::Key::Enter)) {
		selectedCell->isBlocked = !selectedCell->isBlocked;
		hasUpdatedGrid = true;
	}
	selectX = std::clamp(selectX, 0, COLUMNS - 1);
	selectY = std::clamp(selectY, 0, ROWS - 1);
}
