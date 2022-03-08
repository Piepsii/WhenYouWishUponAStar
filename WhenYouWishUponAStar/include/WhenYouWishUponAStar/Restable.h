#pragma once
#include <SFML/Graphics.hpp>
#include "WhenYouWishUponAStar/Component.h"

namespace WhenYouWishUponAStar {

    class Restable :
        public ComponentBase
    {
    public:
        Restable(GameObject* _parent, const ComponentFamilyId _id);
        ~Restable();
        
        void start();
        void update(float _deltaTime);
        void draw(sf::RenderWindow& _window);

    private:
        sf::CircleShape shape;
    };
}
