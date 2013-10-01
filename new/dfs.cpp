#include "dfs.h"

DFS::DFS()
{
	cost = 0;
	nodeNum = 0;
	maxDepth = 0;
	maxFrontier = 0;
	parent = NULL;
	level = NULL;
}
DFS::~DFS()
{
	delete[] parent;
	delete[] level;
}
void DFS::dfs(Maze* maze) 
{
	int size = (maze->width()+1)*(maze->height());
	parent = new int[size];
	level = new int[size];
	for (int i=0; i<size; i++) {
		parent[i] = -1;
		level[i] = -1;
	}
	sx.push( maze->startX() );
	sy.push( maze->startY() );
	nodeNum ++;
	maxFrontier = sx.size();
	int w = maze->width()+1;
	parent[ maze->startX() + maze->startY() * w ] = maze->startX() + maze->startY() * w;
	level[ maze->startX() + maze->startY() * w ] = 0;
	int goal = dfsHelper(maze);
	while (parent[goal] != goal) {
		maze->buffer[goal] = '.';
		goal = parent[goal];
		cost ++;
	}
	for (int i=0; i<size; i++) {
		if (level[i] > maxDepth) 
			maxDepth = level[i];
	}
	maze->buffer[maze->startX() + maze->startY()*(maze->width()+1)] = 'P';
	cout << maze->buffer;
}

int DFS::dfsHelper(Maze* maze)
{
	if (sx.empty()) {
		cout << "failed DFS: empty stack \n";
		return 0;
	}
	if (sx.size()>maxFrontier)
		maxFrontier = sx.size();

	int currX = sx.top();
	int currY = sy.top();
	sx.pop();
	sy.pop();

	int w = (maze->width())+1;
	int end = 1;
	if ( maze->buffer[ currY*( maze->width()+1 )+currX ] == '.') { // arrive at the goal
		end = 1;
		return (currY * w + currX);
	}
	// left down right up
	if (( currX > 0 ) && (parent[ currX-1 + currY * w ] == -1) &&
		(( maze->buffer[ currY*w+currX-1 ] == ' ' ) || ( maze->buffer[ currY*w+currX-1 ] == '.' ))) {
		sx.push( currX-1 );
		sy.push( currY );
		end = 0;
		parent[ currX-1 + currY * w ] = currX + currY * w;
		level[ currX-1 + currY * w ] = level[currX + currY * w] +1;
		nodeNum ++;
	}
	if (( currY < (maze->height()-1) ) && (parent[ currX + (currY+1) * w ] ==-1) &&
		(( maze->buffer[ (currY+1)*w+currX ] == ' ') || ( maze->buffer[ (currY+1)*w+currX ] == '.'))) {
		sx.push( currX );
		sy.push( currY+1 );
		end = 0;
		parent[ currX + (currY+1) * w ] = currX + currY * w;
		level[ currX + (currY+1) * w ] = level[currX + currY * w]+1;
		nodeNum ++;
	}
	if (( currX < ((maze->width())-1) ) && (parent[ currX+1 + currY * w ] ==-1) &&
		(( maze->buffer[ currY*w+currX+1 ] == ' ' ) || ( maze->buffer[ currY*w+currX+1 ] == '.' ))) {
		sx.push( currX+1 );
		sy.push( currY );
		end = 0;
		parent[ currX+1 + currY * w ] = currX + currY * w;
		level[ currX+1 + currY * w ] = level[currX + currY * w]+1;
		nodeNum ++;
	}
	if (( currY > 0 ) && (parent[ currX + (currY-1) * w ] ==-1) &&
		(( maze->buffer[ (currY-1)*w+currX ] == ' ') || ( maze->buffer[ (currY-1)*w+currX ] == '.'))) {
		sx.push( currX );
		sy.push( currY-1 );
		end = 0;
		parent[ currX + (currY-1) * w ] = currX + currY * w;
		level[ currX + (currY-1) * w ] = level[currX + currY * w]+1;
		nodeNum ++;
	}
	return dfsHelper(maze);
}

