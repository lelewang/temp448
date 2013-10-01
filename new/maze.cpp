/* horizontal index is x, vertical index is y */
# include "maze.h"

Maze::Maze(char const & mazeName)
{
	// read the maze
	// make sure there is a \n at the end of each row, and no extra rows
  	fstream mazePic;
  	mazePic.open (&mazeName);
    mazePic.seekg (0, mazePic.end);
    int length = mazePic.tellg();
    mazePic.seekg (0, mazePic.beg);
    buffer = new char [length+1];
    mazePic.read (buffer,length);
    if (mazePic)  {
      //cout << buffer;
    }
    else
      cout << "error: only " << mazePic.gcount() << " could be read";
  	mazePic.close(); 
  	 
  	// build the map
    mW =0;
    while (buffer[mW] != '\n') {
      mW ++;
    }
    mH = length/(mW+1);
    
    for ( int i=0; i<mH; i++ ) {
      for ( int j=0; j<mW; j++) {
        if (buffer[j+(mW+1)*i] == 'P') { 
      	  sX = j;
      	  sY = i;
      	 }
        else if (buffer[j+(mW+1)*i] == '.') {
          endX.push_back(i);
          endY.push_back(j);
        }
      }
  	} 
    //cout<< " Width "<< mW << " Height " << mH <<'\n';
  	//cout << " start " << sX << ' ' << sY << " end "<< eX << ' ' << eY <<'\n';
}

Maze::~Maze()
{
	delete [] buffer;
  endX.clear();
  endY.clear();
}

int Maze::width() const
{
	return mW;
}

int Maze::height() const
{
	return mH;
}

int Maze::startX() const
{
	return sX;
}

int Maze::startY() const 
{
	return sY;
}

void Maze::newStart(int x, int y)
{
  sX = x;
  sY = y;
}
