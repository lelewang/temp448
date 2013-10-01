#include "bfs.h"
#include "node.h"

BFS::BFS()
{
	pathCost = 0;
	nodeNum = 0;
	expanded.clear();
	frontier.clear();
}
BFS::~BFS()
{
	for (int i=0; i<frontier.size(); i++) {
		delete[] frontier[i];
	}
	for (int i=0; i<expanded.size(); i++) {
		delete[] expanded[i];
	}
	frontier.clear();
	expanded.clear();
	resultx.clear();
	resulty.clear();
}
void BFS::bfs(Maze* maze) 
{
	int size = (maze->width()+1)*(maze->height());
	vector<int> v1;
	v1.clear();
	vector<int> v2;
	v2.clear();
	Node* root = new Node(maze->startX(), maze->startY(), v1, v2);
	frontier.push_back( root );
   
   	
	int w = maze->width()+1; 
	int pathCost = bfsHelper(maze);
	cout <<pathCost << '\n';
	if (pathCost != -1) {
		for (int i=0; i<resultx.size(); i++) {
			unsigned char mark = (i <= 9)? (0x30 + i):(0x40 + i - 9);
			maze->buffer[ resultx[i]+resulty[i]*w ] = mark;
		}
		cout << maze->buffer;
  	}
}

int BFS::bfsHelper(Maze* maze)
{
	if (frontier.empty()) {
		cout << "failed BFS: empty queue \n";
		return 0;
	}
/*
	if (nodeNum > 4000) {
		cout << "too many nodes \n";
		return -1;
	}
*/
	Node* currNode = frontier.front();
	frontier.pop_front();
	vector<int> vx;
	vector<int> vy;

	for( int i=0; i<currNode->gx.size(); i++) {
		vx.push_back(currNode->gx[i]);
		vy.push_back(currNode->gy[i]);
	}
	int currCost = currNode->cost;
	expanded.push_back( currNode );
	nodeNum ++;
	cout << nodeNum <<'\n';
	int w = (maze->width())+1;
	if ( maze->buffer[ (currNode->ny*( maze->width()+1 ))+currNode->nx ] == '.') { // arrive at the goal
		if ( !validNode(currNode) ) {// current position's goal hasn't reached before
			vx.push_back(currNode->nx);
			vy.push_back(currNode->ny);
			if (vx.size() == maze->endX.size()) // all the goals are found
			{
				for (int i=0; i<vx.size(); i++) {
					resultx.push_back(vx[i]);
					resulty.push_back(vy[i]);
				}
				return currCost;
			}
			Node* newStart = new Node( currNode->nx, currNode->ny, vx, vy);
			newStart->cost = currCost;
			frontier.push_back(newStart);
		}
	}
	
	if ((currNode->nx > 0) && (maze->buffer[currNode->ny * w + currNode->nx-1] != '%')) {
		if (!frontierExist( currNode->nx-1, currNode->ny, vx, vy) && (!expandedExist( currNode->nx-1, currNode->ny, vx, vy))) {
			Node* newNode = new Node( currNode->nx-1, currNode->ny, vx, vy);
			newNode->cost = currCost +1;
			frontier.push_back(newNode);
			//cout<< "L" << '\n';
		}
	}
	if ((currNode->ny < (maze->height()-1)) && (maze->buffer[(currNode->ny+1) * w + currNode->nx] != '%')) {
		if (!frontierExist( currNode->nx, currNode->ny+1, vx, vy) && (!expandedExist( currNode->nx, currNode->ny+1, vx, vy))) {
			Node* newNode = new Node( currNode->nx, currNode->ny+1, vx, vy);
			newNode->cost = currCost +1;
			frontier.push_back(newNode);
			//cout<< "D" << '\n';
		}
	}
	if ((currNode->nx < (maze->width()-1)) && (maze->buffer[currNode->ny * w + currNode->nx+1] != '%')) {
		if (!frontierExist( currNode->nx+1, currNode->ny, vx, vy) && (!expandedExist( currNode->nx+1, currNode->ny, vx, vy))) {
			Node* newNode = new Node( currNode->nx+1, currNode->ny, vx, vy);
			newNode->cost = currCost +1;
			frontier.push_back(newNode);
			//cout<< "R" << '\n';
		}
	}
	if ((currNode->ny > 0) && (maze->buffer[(currNode->ny-1) * w + currNode->nx] != '%')) {
		if (!frontierExist( currNode->nx, currNode->ny-1, vx, vy) && (!expandedExist( currNode->nx, currNode->ny-1, vx, vy))) {
			Node* newNode = new Node( currNode->nx, currNode->ny-1, vx, vy);
			newNode->cost = currCost +1;
			frontier.push_back(newNode);
			//cout<< "U" << '\n';
		}
	}
	
	return bfsHelper(maze);
}

bool BFS::validNode(Node* node) {
	for (int i=0; i<node->gx.size(); i++) {
		if ((node->nx == node->gx[i]) && (node->ny == node->gy[i]))
			return true; // this goal has found
	}
	return false;
}

bool BFS::expandedExist(int x, int y, vector<int> vx, vector<int> vy)
{
	for(int i=0; i<expanded.size(); i++) {
		if (((expanded[i])->nx == x) && ((expanded[i])->ny == y) 
			&& ((expanded[i])->gx == vx) && ((expanded[i])->gy == vy)) {
			return true;
		}
	}
	return false;
}

bool BFS::frontierExist(int x, int y, vector<int> vx, vector<int> vy)
{
	for(int i=0; i<frontier.size(); i++) {
		if (((frontier[i])->nx == x) && ((frontier[i])->ny == y) 
			&& ((frontier[i])->gx == vx) && ((frontier[i])->gy == vy)) {
			return true;
		}
	}
	return false;
}









