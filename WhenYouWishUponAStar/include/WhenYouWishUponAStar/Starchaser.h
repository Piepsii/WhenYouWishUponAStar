#pragma once
#include "WhenYouWishUponAStar/Component.h"

namespace WhenYouWishUponAStar {

    class Node;

    enum class StarchaserState {
        Searching,
        Moving,
        Selling,
        Resting
    };

    class Starchaser :
        public ComponentBase
    {
    public:
        Starchaser(GameObject* _parent, const ComponentFamilyId _id);
        ~Starchaser();

        void start();
        void decide();
        void update(float _deltaTime);

    private:
        bool hasFallenStar = false;
        int stamina = 5;
        float moveSpeed = 1.0f;
        float restSpeed = 1.0f;
        float sellSpeed = 1.0f;

        StarchaserState state = StarchaserState::Searching;
        Node* target;
        Node* fallenStar;
        Node* spaceship;
        Node* tradingPost;
    };
}
