#pragma once

#include <vector>
#include "Node.h"

class Path
{
public:
	Path();

private:
	std::vector<Node> open;
	std::vector<Node> closed;
};

