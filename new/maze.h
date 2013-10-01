
#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Maze {
	public:
		Maze(char const & mazeName);
		~Maze();
		char* buffer;
		int width() const;
		int height() const;
		int startX() const;
		int startY() const;
		void newStart(int x, int y);
		vector<int> endX;
		vector<int> endY;
		
	private:
		int mW;
		int mH;
		int sX;
		int sY;
		
};

#endif