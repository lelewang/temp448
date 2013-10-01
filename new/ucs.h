#ifndef UCS_H
#define UCS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <queue>
#include "maze.h"

using namespace std;

class UCS {
	public: 
	 	UCS();
	 	~UCS();
		void ucs(Maze* maze, int fn);
		int cost;
		int nodeNum;
		int maxDepth;
		int maxFrontier;
		int* parent; 
		int* level;
		vector<int> vx;
		vector<int> vy;
	private:
		int ucsHelper(Maze* maze, int fn);
		double c1(int x);
		double c2(int x);
};

#endif