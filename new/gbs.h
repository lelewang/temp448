#ifndef GBS_H
#define GBS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <queue>
#include "maze.h"

using namespace std;

class GBS {
	public: 
		GBS();
		~GBS();
		void gbs(Maze* maze);
		int cost;
		int nodeNum;
		int maxDepth;
		int maxFrontier;
		int* parent; 
		int* level;
		vector<int> vx;
		vector<int> vy;
	private:
		int gbsHelper(Maze* maze);
};

#endif