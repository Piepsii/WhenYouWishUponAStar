#pragma once

namespace WhenYouWishUponAStar {

    class JPSNode
    {
    public:
        JPSNode(sf::Vector2i _pos);

        sf::Vector2i pos;
        int f = 0;
        int g = 0;
        int h = INT_MAX;
        JPSNode* parent{nullptr};
        bool closed = false;
    };

}
