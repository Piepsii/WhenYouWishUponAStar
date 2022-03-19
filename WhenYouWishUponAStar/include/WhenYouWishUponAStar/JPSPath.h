#pragma once

#include <SFML/Graphics.hpp>
#include "WhenYouWishUponAStar/Component.h"
#include "WhenYouWishUponAStar/JPSNode.h"
#include "WhenYouWishUponAStar/Grid.h"

namespace WhenYouWishUponAStar {

    class JPSPath :
        public ComponentBase
    {
    public:
        JPSPath(GameObject* _parent, const ComponentFamilyId _id);

        void setGrid(Grid& _grid);
        std::vector<sf::Vector2i> find(int _sX, int _sY, int _tX, int _tY);
        sf::Vector2i nextPosition(sf::Vector2i _current);

        bool isFound = false;

    private:
        int manhattan(int _x, int _y);
        void identifySuccessors(sf::Vector2i _pos, bool _first = false);
        JPSNode* jump(sf::Vector2i _this, sf::Vector2i _next);
        JPSNode* getNode(sf::Vector2i _pos);
        JPSNode* createNode(sf::Vector2i _pos);
        JPSNode* forcedNeighborCheck(sf::Vector2i _this, sf::Vector2i _direction, sf::Vector2i _offset);
        std::vector<sf::Vector2i> neighborsFromDirection(sf::Vector2i _direction);

        sf::Vector2i start;
        sf::Vector2i target;
        sf::Vector2i current;
        std::vector<JPSNode*> open;
        std::vector<JPSNode> nodes;
        Grid* grid;
    };

}

