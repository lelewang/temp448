#include <iostream>
#include <fstream>
#include <string>
#include "maze.h"
#include "bfs.h"
/*#include "dfs.h"
#include "gbs.h"
#include "ass.h"
#include "ucs.h"*/

using namespace std;

int main (int argc, char* argv[]) {
  
	char* mazeName =argv[1];
  Maze maze = Maze(*mazeName);

  int method = atoi(argv[2]);

  if (method == 0) { //bfs
    BFS search;
    search.bfs(&maze);
    cout << "Breath First Search" << '\n';
    cout << "path cost "<< search.pathCost << '\n';
    cout << "expanded node number "<< search.nodeNum << '\n';
  }
/*
  if (method == 1) { //dfs
    DFS search;
    search.dfs(&maze);
    cout << "Depth First Search" << '\n';
    cout << "path cost "<< search.cost << '\n';
    cout << "expanded node number "<< search.nodeNum << '\n';
    cout << "maximum depth "<< search.maxDepth << '\n';
    cout << "maximum frontier "<< search.maxFrontier << '\n';
  }
  if (method == 2) { //gbs
    GBS search;
    search.gbs(&maze);
    cout << "Greedy Best-first Search" << '\n';
    cout << "path cost "<< search.cost << '\n';
    cout << "expanded node number "<< search.nodeNum << '\n';
    cout << "maximum depth "<< search.maxDepth << '\n';
    cout << "maximum frontier "<< search.maxFrontier << '\n';
  }
  if (method == 3) { //as
    ASS search;
    search.ass(&maze);
    cout << "A Star Search" << '\n';
    cout << "path cost "<< search.cost << '\n';
    cout << "expanded node number "<< search.nodeNum << '\n';
    cout << "maximum depth "<< search.maxDepth << '\n';
    cout << "maximum frontier "<< search.maxFrontier << '\n';
  }
  if (method == 4) { //ucs input c1 or c2
    int fn;
    cout << "Uniformed Cost Search with cost function, please choose cost function ";
    cin >> fn;
    UCS search;
    search.ucs(&maze,fn);
    cout << "path cost "<< search.cost << '\n';
    cout << "expanded node number "<< search.nodeNum << '\n';
    cout << "maximum depth "<< search.maxDepth << '\n';
    cout << "maximum frontier "<< search.maxFrontier << '\n';
  }

*/
  	return 0;
}