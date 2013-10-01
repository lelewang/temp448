#ifndef DFS_H
#define DFS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stack>
#include "maze.h"

using namespace std;

class DFS {
	public: 
		DFS();
		~DFS();
		void dfs(Maze* maze);
		int cost;
		int nodeNum;
		int maxDepth;
		int maxFrontier;
		int* parent; 
		int* level;
		stack<int> sx;
		stack<int> sy;
	private:
		int dfsHelper(Maze* maze);
};

#endif