#include "WhenYouWishUponAStar/Starchaser.h"

namespace WhenYouWishUponAStar {

	Starchaser::Starchaser(GameObject* _parent, const ComponentFamilyId _id)
		: ComponentBase(_parent, _id)
	{
	}

	Starchaser::~Starchaser()
	{
	}

	void Starchaser::sense(CellObject& _starchaser, 
						   CellObject& _fallenStar,
						   CellObject& _spaceship,
						   CellObject& _tradingPost,
						   AStarPath& _path,
						   JPSPath& _jpsPath)
	{
		starchaser = &_starchaser;
		fallenStar = &_fallenStar;
		spaceship = &_spaceship;
		tradingPost = &_tradingPost;
		path = &_path;
		jpsPath = &_jpsPath;
	}

	void Starchaser::decide()
	{
		if (starchaser->cell == fallenStar->cell
			&& target == fallenStar->cell) {
			hasFallenStar = true;
			path->isFound = false;
			jpsPath->isFound = false;
		}

		if (starchaser->cell == tradingPost->cell
			&& target == tradingPost->cell
			&& hasFallenStar) {
			state = StarchaserState::Selling;
			path->isFound = false;
			jpsPath->isFound = false;
			return;
		}

		if (starchaser->cell == spaceship->cell
			&& target == spaceship->cell
			&& stamina < maxStamina) {
			state = StarchaserState::Resting;
			path->isFound = false;
			jpsPath->isFound = false;
			return;
		}

		if (stamina <= 0
			&& hasFallenStar) {
			target = spaceship->cell;
			hasFallenStar = false;
			state = StarchaserState::Searching;
			return;
		}

		if (path->isFound || jpsPath->isFound) {
			state = StarchaserState::Moving;
			return;
		} 


		if (!hasFallenStar) {
			target = fallenStar->cell;
			state = StarchaserState::Searching;
			return;
		}

		if (hasFallenStar) {
			target = tradingPost->cell;
			state = StarchaserState::Searching;
			return;
		}

	}

	void Starchaser::act(float _deltaTime)
	{
		switch (state) {
		case StarchaserState::Searching:
			if (usesAStar) {
				path->find(starchaser->x, starchaser->y, target->x, target->y);
			}
			else {
				jpsPath->find(starchaser->x, starchaser->y, target->x, target->y);
			}
			break;
		case StarchaserState::Moving:
			moveCounter += _deltaTime;
			if (moveCounter >= moveSpeed) {
				moveCounter = 0.0f;
				Cell* nextCell;
				if (usesAStar) {
					nextCell = path->nextCell(*starchaser->cell);
				}
				else {
					auto pos = jpsPath->nextPosition(sf::Vector2i(starchaser->cell->x,
													   starchaser->cell->y));
					nextCell = starchaser->grid->getCell(pos);
				}
				starchaser->moveTo(*nextCell);
				if (hasFallenStar) {
					fallenStar->moveTo(*nextCell);
					stamina--;
				}
			}
			break;
		case StarchaserState::Selling:
			hasFallenStar = false;
			fallenStar->respawn();
			break;
		case StarchaserState::Resting:
			restCounter += _deltaTime;
			starchaser->setRotation(restCounter / restSpeed * 360.0f);
			if (restCounter >= restSpeed) {
				restCounter = 0.0f;
				stamina++;
			}
			break;
		}
	}

	void Starchaser::update(float _deltaTime)
	{
		decide();
		act(_deltaTime);
	}
}
