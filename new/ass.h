#ifndef ASS_H
#define ASS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <queue>
#include "maze.h"

using namespace std;

class ASS {
	public: 
	 	ASS();
	 	~ASS();
		void ass(Maze* maze);
		int cost;
		int nodeNum;
		int maxDepth;
		int maxFrontier;
		int* parent; 
		int* level;
		vector<int> vx;
		vector<int> vy;
	private:
		int assHelper(Maze* maze);
};

#endif