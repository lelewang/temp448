#include "ucs.h"
#include "math.h"

UCS::UCS()
{
	cost = 0;
	nodeNum = 0;
	maxDepth = 0;
	maxFrontier = 0;
	parent = NULL;
	level = NULL;
}
UCS::~UCS()
{
	delete[] parent;
	delete[] level;
}
void UCS::ucs(Maze* maze, int fn) 
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
	maxFrontier = vx.size();
	int w = maze->width()+1;
	parent[ maze->startX() + maze->startY() * w ] = maze->startX() + maze->startY() * w;
	level[ maze->startX() + maze->startY() * w ] = 0;
	int goal = ucsHelper(maze, fn);
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

int UCS::ucsHelper(Maze* maze, int fn)
{
	int w = (maze->width())+1;
	if (vx.empty()) {
		cout << "failed UCS: empty vector \n";
		return 0;
	}
	if (vx.size()>maxFrontier)
		maxFrontier = vx.size();

	int currX = vx.front();
	int currY = vy.front();
	int idx = 0;

	for (int i=0; i<vx.size(); i++) {
		if (fn == 1) {//c1 = 1/2^x;
			if ( c1(vx[i]) < c1(currX) ) {
				currX = vx[i];
				currY = vy[i];
				idx = i;
			}
		}
		if (fn == 2) {
			if ( c2(vx[i]) < c2(currX) ) {
				currX = vx[i];
				currY = vy[i];
				idx = i;
			}
		}
	}
	vx.erase(vx.begin()+idx);
	vy.erase(vy.begin()+idx);
	nodeNum ++;

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
	}
	if (( currY < (maze->height()-1) ) && (parent[ currX + (currY+1) * w ] ==-1) &&
		(( maze->buffer[ (currY+1)*w+currX ] == ' ') || ( maze->buffer[ (currY+1)*w+currX ] == '.'))) {
		vx.push_back( currX );
		vy.push_back( currY+1 );
		parent[ currX + (currY+1) * w ] = currX + currY * w;
		level[ currX + (currY+1) * w ] = level[currX + currY * w]+1;
	}
	if (( currX < ((maze->width())-1) ) && (parent[ currX+1 + currY * w ] ==-1) &&
		(( maze->buffer[ currY*w+currX+1 ] == ' ' ) || ( maze->buffer[ currY*w+currX+1 ] == '.' ))) {
		vx.push_back( currX+1 );
		vy.push_back( currY );
		parent[ currX+1 + currY * w ] = currX + currY * w;
		level[ currX+1 + currY * w ] = level[currX + currY * w]+1;
	}
	if (( currY > 0 ) && (parent[ currX + (currY-1) * w ] ==-1) &&
		(( maze->buffer[ (currY-1)*w+currX ] == ' ') || ( maze->buffer[ (currY-1)*w+currX ] == '.'))) {
		vx.push_back( currX );
		vy.push_back( currY-1 );
		parent[ currX + (currY-1) * w ] = currX + currY * w;
		level[ currX + (currY-1) * w ] = level[currX + currY * w]+1;
	}
	return ucsHelper(maze, fn);
}
double UCS::c1(int x)
{
	return pow(0.5,x);
}
double UCS::c2(int x)
{
	return pow(2,x);
}
