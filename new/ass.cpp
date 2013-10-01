#include "ass.h"
#include "math.h"

ASS::ASS()
{
	cost = 0;
	nodeNum = 0;
	maxDepth = 0;
	maxFrontier = 0;
	parent = NULL;
	level = NULL;
}
ASS::~ASS()
{
	delete[] parent;
	delete[] level;
}
void ASS::ass(Maze* maze) 
{
	int size = (maze->width()+1)*(maze->height());
	parent = new int[size];
	level = new int[size];
	for (int i=0; i<size; i++) {
		parent[i] = -1;
		level[i] = -1;
	}
	vx.push_back( maze->startX() );
	vy.push_back( maze->startY() );
	nodeNum++;
	maxFrontier = vx.size();
	int w = maze->width()+1;
	parent[ maze->startX() + maze->startY() * w ] = maze->startX() + maze->startY() * w;
	level[ maze->startX() + maze->startY() * w ] = 0;
	int goal = assHelper(maze);
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

int ASS::assHelper(Maze* maze)
{
	int w = (maze->width())+1;
	if (vx.empty()) {
		cout << "failed ASS: empty vector \n";
		return 0;
	}
	if (vx.size()>maxFrontier)
		maxFrontier = vx.size();

	int currX = vx.front();
	int currY = vy.front();
	int idx = 0;
	for (int i=0; i<vx.size(); i++) {
		if ((abs( vx[i] - maze->endX()) + abs(vy[i] - maze->endY()) + level[ vx[i] + vy[i] * w ] ) 
			< (abs( currX - maze->endX()) + abs(currY - maze->endY()) + level[ currX + currY * w] )) {
			currX = vx[i];
			currY = vy[i];
			idx = i;
		}
	}
	vx.erase(vx.begin()+idx);
	vy.erase(vy.begin()+idx);

	if ( maze->buffer[ currY*( maze->width()+1 )+currX ] == '.') { // arrive at the goal
		return (currY * w + currX);
	}
	// left down right up
	if (( currX > 0 ) && (parent[ currX-1 + currY * w ] == -1) &&
		(( maze->buffer[ currY*w+currX-1 ] == ' ' ) || ( maze->buffer[ currY*w+currX-1 ] == '.' ))) {
		vx.push_back( currX-1 );
		vy.push_back( currY );
		parent[ currX-1 + currY * w ] = currX + currY * w;
		level[ currX-1 + currY * w ] = level[currX + currY * w] +1;
		nodeNum++;
	}
	if (( currY < (maze->height()-1) ) && (parent[ currX + (currY+1) * w ] ==-1) &&
		(( maze->buffer[ (currY+1)*w+currX ] == ' ') || ( maze->buffer[ (currY+1)*w+currX ] == '.'))) {
		vx.push_back( currX );
		vy.push_back( currY+1 );
		parent[ currX + (currY+1) * w ] = currX + currY * w;
		level[ currX + (currY+1) * w ] = level[currX + currY * w]+1;
		nodeNum++;
	}
	if (( currX < ((maze->width())-1) ) && (parent[ currX+1 + currY * w ] ==-1) &&
		(( maze->buffer[ currY*w+currX+1 ] == ' ' ) || ( maze->buffer[ currY*w+currX+1 ] == '.' ))) {
		vx.push_back( currX+1 );
		vy.push_back( currY );
		parent[ currX+1 + currY * w ] = currX + currY * w;
		level[ currX+1 + currY * w ] = level[currX + currY * w]+1;
		nodeNum++;
	}
	if (( currY > 0 ) && (parent[ currX + (currY-1) * w ] ==-1) &&
		(( maze->buffer[ (currY-1)*w+currX ] == ' ') || ( maze->buffer[ (currY-1)*w+currX ] == '.'))) {
		vx.push_back( currX );
		vy.push_back( currY-1 );
		parent[ currX + (currY-1) * w ] = currX + currY * w;
		level[ currX + (currY-1) * w ] = level[currX + currY * w]+1;
		nodeNum++;
	}
	return assHelper(maze);
}
