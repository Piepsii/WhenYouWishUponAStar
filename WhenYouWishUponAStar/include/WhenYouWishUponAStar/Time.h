#pragma once
#include <SFML/System.hpp>

namespace WhenYouWishUponAStar {

	class Time
	{
	public:
		static bool update();

		static float time, deltaTime;
		static float timeScale;

	private:
		static sf::Clock simClock, deltaClock;
	};
}
