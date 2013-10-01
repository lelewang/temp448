#ifndef BFS_H
#define BFS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include  "node.h"
#include "maze.h"

using namespace std;

class BFS {
	public: 
		BFS();
		~BFS();
		void bfs(Maze* maze);
		int pathCost;
		int nodeNum;
		deque<Node*> frontier;
		vector<Node*> expanded;
		vector<int> resultx;
		vector<int> resulty;
	private:
		int bfsHelper(Maze* maze);
		bool expandedExist(int x, int y, vector<int> vx, vector<int> vy);
		//int nextNode(); // find the node from frontier for expansion
		bool frontierExist(int x, int y, vector<int> vx, vector<int> vy);
		bool validNode(Node* node); // whether the goal at current position is reached before
};

#endif