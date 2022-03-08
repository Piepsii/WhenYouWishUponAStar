#pragma once

#include <vector>
#include "Node.h"
#include "Grid.h"
#include "WhenYouWishUponAStar/Component.h"

namespace WhenYouWishUponAStar {

	class Path
		: public ComponentBase
	{
	public:
		Path(GameObject* _parent, const ComponentFamilyId _id);
		~Path();

		void initPath(Grid& _grid, int _sX, int _sY, int _tX, int _tY);

		void find();
		bool isNodeInList(Node* _node, std::vector<Node*> _list);

	private:
		int manhattan(int _x, int _y);

		Node* start;
		Node* target;
		Node* current;
		std::vector<Node*> open;
		std::vector<Node*> closed;
		Grid* grid;
	};
}
