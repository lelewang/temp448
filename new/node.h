#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

class Node {
	public: 
	 	Node(int x, int y, vector<int> gx1, vector<int> gy1);
	 	Node(); 
	 	~Node();
	 	Node(const Node& n);
	 	int nx;
	 	int ny;
	 	vector<int> gx;
	 	vector<int> gy;
	 	int cost;
	 	//int hfun;
};

#endif