#pragma once

#include <vector>
#include "AStarNode.h"
#include "Grid.h"
#include "WhenYouWishUponAStar/Component.h"

namespace WhenYouWishUponAStar {

	class AStarPath
		: public ComponentBase
	{
	public:
		AStarPath(GameObject* _parent, const ComponentFamilyId _id);
		~AStarPath();

		void setupPath(Grid& _grid, int _sX, int _sY, int _tX, int _tY);
		AStarNode* find();


	private:
		int manhattan(int _x, int _y);
		bool isNodeInList(AStarNode* _node, std::vector<AStarNode*> _list);
		AStarNode* createNode(Cell& _cell);

		AStarNode* start;
		AStarNode* target;
		AStarNode* current;
		std::vector<AStarNode*> open;
		std::vector<AStarNode*> closed;
		std::vector<std::unique_ptr<AStarNode>> nodes;
		Grid* grid;
	};
}
