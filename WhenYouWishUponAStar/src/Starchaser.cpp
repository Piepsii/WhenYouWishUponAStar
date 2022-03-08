#include "WhenYouWishUponAStar/Starchaser.h"

namespace WhenYouWishUponAStar {

	Starchaser::Starchaser(GameObject* _parent, const ComponentFamilyId _id)
		: ComponentBase(_parent, _id)
	{
	}

	Starchaser::~Starchaser()
	{
	}

	void Starchaser::start()
	{
	}

	void Starchaser::decide()
	{
		if (stamina >= 0) {
			target = spaceship;
			return;
		}

		if(!hasFallenStar) {
			target = fallenStar;
			return;
		}

		if (hasFallenStar) {
			target = tradingPost;
			return;
		}
	}

	void Starchaser::update(float _deltaTime)
	{
		switch (state) {
		case StarchaserState::Searching:
			// set Node* to possible targets
			
			// animate path find
			break;
		case StarchaserState::Moving:
			// move towards target
			if(hasFallenStar)
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
}
