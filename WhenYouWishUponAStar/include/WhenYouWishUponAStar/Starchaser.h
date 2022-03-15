#pragma once
#include "WhenYouWishUponAStar/Component.h"
#include "WhenYouWishUponAStar/CellObject.h"
#include "WhenYouWishUponAStar/AStarPath.h"

namespace WhenYouWishUponAStar {

    class Cell;

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

        void sense(CellObject& _starchaser,
                   CellObject& _fallenStar,
                   CellObject& _spaceship,
                   CellObject& _tradingPost,
                   AStarPath& _path);
        void decide();
        void act(float _deltaTime);
        void update(float _deltaTime);

    private:
        bool hasFallenStar = false;
        int stamina = 5, maxStamina = 5;
        float moveSpeed = 0.3f, moveCounter = 0.0f;
        float restSpeed = 0.3f, restCounter = 0.0f;

        StarchaserState state = StarchaserState::Searching;
        Cell* target;
        CellObject* starchaser;
        CellObject* fallenStar;
        CellObject* spaceship;
        CellObject* tradingPost;
        AStarPath* path;
    };
}
