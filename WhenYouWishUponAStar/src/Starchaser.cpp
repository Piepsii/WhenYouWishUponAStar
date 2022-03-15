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
						   AStarPath& _path)
	{
		starchaser = &_starchaser;
		fallenStar = &_fallenStar;
		spaceship = &_spaceship;
		tradingPost = &_tradingPost;
		path = &_path;
	}

	void Starchaser::decide()
	{
		if (starchaser->cell == fallenStar->cell
			&& target == fallenStar->cell) {
			hasFallenStar = true;
			path->isFound = false;
		}

		if (starchaser->cell == tradingPost->cell
			&& target == tradingPost->cell
			&& hasFallenStar) {
			state = StarchaserState::Selling;
			path->isFound = false;
			return;
		}

		if (starchaser->cell == spaceship->cell
			&& target == spaceship->cell
			&& stamina < maxStamina) {
			state = StarchaserState::Resting;
			path->isFound = false;
			return;
		}

		if (stamina <= 0
			&& hasFallenStar) {
			target = spaceship->cell;
			hasFallenStar = false;
			state = StarchaserState::Searching;
			return;
		}

		if (path->isFound) {
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
			path->find(starchaser->x, starchaser->y, target->x, target->y);
			break;
		case StarchaserState::Moving:
			moveCounter += _deltaTime;
			if (moveCounter >= moveSpeed) {
				moveCounter = 0.0f;
				starchaser->moveTo(*path->nextCell(*starchaser->cell));
				if (hasFallenStar) {
					fallenStar->moveTo(*path->nextCell(*starchaser->cell));
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
