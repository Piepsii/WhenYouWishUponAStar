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
		if (path->isFound) {
			state = StarchaserState::Moving;

		} 
		else {
			state = StarchaserState::Searching;
			if (stamina <= 0) {
				target = spaceship->cell;
				return;
			}

			if (!hasFallenStar) {
				target = fallenStar->cell;
				return;
			}

			if (hasFallenStar) {
				target = tradingPost->cell;
				return;
			}
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
				starchaser->moveTo(*path->nextCell(*starchaser->cell));
				moveCounter = 0.0f;
			}
			if (hasFallenStar)
				stamina--;
			break;
		case StarchaserState::Selling:
			hasFallenStar = false;
			break;
		case StarchaserState::Resting:
			stamina++;
			break;
		}
	}

	void Starchaser::update(float _deltaTime)
	{
		decide();
		act(_deltaTime);
	}
}
