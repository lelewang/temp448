#include "node.h"

Node::Node(int x, int y, vector<int> gx1, vector<int> gy1)
{
	nx = x;
	ny = y;
	cost = 0;
	for (int i=0; i<gx1.size(); i++) {
		gx.push_back(gx1[i]);
		gy.push_back(gy1[i]);
	}
}

Node::~Node()
{
	gx.clear();
	gy.clear();
}
Node::Node()
{
	nx= 0;
	ny=0;
	cost = 0;
	gx.push_back(0);
	gy.push_back(0);
}

Node::Node(const Node& n) 
{
	nx = n.nx;
	ny = n.ny;
	cost = n.cost;
	for (int i=0 ; i<1; ++i)
	{
		gx.push_back((n.gx)[i]);
		gy.push_back((n.gy)[i]);
	}
}

