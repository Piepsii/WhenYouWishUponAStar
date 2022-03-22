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
        void draw(sf::RenderWindow& _window);
        void setGrid(Grid& _grid);
        bool find(int _sX, int _sY, int _tX, int _tY);
        sf::Vector2i nextPosition(sf::Vector2i _current);
        void forget();

        bool isFound = false;

    private:
        void clear();
        void identifySuccessors(sf::Vector2i _pos);
        int manhattan(int _x, int _y);
        int calcG(sf::Vector2i _current, sf::Vector2i _new, int _g);
        bool containsOpenNodes();
        bool forcedNeighborCheck(sf::Vector2i _this, sf::Vector2i _direction, sf::Vector2i _offset);
        JPSNode* getNode(sf::Vector2i _pos);
        JPSNode* createNode(sf::Vector2i _pos);
        sf::Vector2i jump(sf::Vector2i _this, sf::Vector2i _next);
        std::vector<sf::Vector2i> neighborsFromDirection(JPSNode* _node);
        std::vector<sf::Vector2i> createPath();

        sf::Color colorPath = sf::Color::Green;
        sf::Color colorNodes = sf::Color::Red;
        sf::Vector2i start;
        sf::Vector2i target;
        sf::Vector2i current;
        std::vector<JPSNode> nodes;
        std::vector<sf::Vector2i> path;
        Grid* grid;
    };

}

