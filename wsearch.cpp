/* Marlena Skall
   1/24/17
   CSCI 104
   Problem #5
   Word Search
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Location
{
  Location()
  {
    row = -1;
    col = -1;
  }
  Location(int r, int c)
  {
    row = r;
    col = c;
  }
  int row;
  int col;
};

// @param[in] instream - Input (file) stream for the input file.  Opened in main()
// @param[out] grid Blank vector of vectors.  Should be updated with the
//                  contents of the grid from the input file
// @return true if successful, false otherwise (see HW writeup for details
//         about possible error cases to be checked)
bool readGrid(istream& instream, vector<vector<char> >& grid )
{
   /** You complete **/
   
   //create a vector for rows to begin the row portion of the grid
   //in order to read in the letters of the grid, create a char variable
   //also create a string in order to read in the lines of the grid
   vector<char> row;
   char r;
   string line;
   
   int length = 1;
   //while loop that reads each new line
   while(getline(instream, line))
   {
      if(instream.fail())
      {
         cout << "Couldn't read line" << endl;
         return false;
      }
      
      //create a stringstream to read in each letter of the line
      stringstream ss(line);
      //int i = 0; //counter to know if the length of chars in line is same
      
      while(ss >> r)
      {
         //push each new letter from the line into the vector
         row.push_back(r);
      }
      
      grid.push_back(row); //finally push the chars read in to vector
      length++;
      row.clear(); //need to clear the row or else nothing will update
   }
   
   //check that grid is valid
   for(int i = 0; i < grid.size(); i++)
   {
      if(grid[i].size() != length)
      {
         //cout << "Invalid grid" << endl;
         return false;
      }
   }
   
   //testing to see what prints out what for call of .size()
   //cout << grid[0].size() << endl; //columns
   //cout << grid.size() << endl; //rows
  
   //*************PRINT GRID************
   /*for(int i = 0; i < 4; i++)
   {
      for(int j = 0; j < 5; j++)
      {
         cout << grid[i][j] << " "; 
      }
      cout << endl;
   }*/
   //*************PRINT GRID************
   
   //if everything checks out and a successful grid is created, return true
   return true; 
   
}

// prototype - will be implemented below
bool findWordHelper(
   const vector<vector<char> >& grid, 
   Location currLoc,
   Location delta,
   string word,
   unsigned int currWordIndex);

// Do not change
void printSolution(const string& targetWord, const Location& start, string direction)
{
  cout << targetWord << " starts at (row,col) = (" << start.row << "," << start.col
       << ") and proceeds " << direction << "." << endl;
}

// Do not change
void printNoSolution(const string& targetWord)
{
  cout << targetWord << " does NOT occur." << endl;
}

// Complete - you should not need to change this.
void findWord(const vector<vector<char> >& grid, 
	      const string& targetWord)
{
  bool found = false;
  if(targetWord.size() < 2){
    cout << "Need a word of length 2 or more." << endl;
    return;
  }
  for(unsigned int r=0; r < grid.size(); r++){
    for(unsigned int c=0; c < grid[r].size(); c++){
      if(grid[r][c] == targetWord[0]){
	Location loc(r,c);
	if( findWordHelper(grid, Location(r-1,c), Location(-1, 0), targetWord, 1) ){
	  printSolution(targetWord, loc, "up");
	  found = true;
	}
	if( findWordHelper(grid, Location(r,c-1), Location(0,-1), targetWord, 1) ){
	  printSolution(targetWord, loc, "left");
	  found = true;
	}
	if( findWordHelper(grid, Location(r+1,c), Location(1, 0), targetWord, 1) ){
	  printSolution(targetWord, loc, "down");
	  found = true;
	}
	if( findWordHelper(grid, Location(r,c+1), Location(0,1), targetWord, 1) ){
	  printSolution(targetWord, loc, "right");
	  found = true;
	}
      }      
    }
  }
  if(!found){
    printNoSolution(targetWord);
  }
}

/**
 * @param[in] grid The 2D vector containing the entire search contents
 * @param[in] currLoc Current row and column location to try to match 
 *                    with the next letter
 * @param[in] delta   Indicates direction to move for the next search
 *                    by containing the *change* in row, col values
 *                    (i.e. 1,0 = down since adding 1 will move down 1 row)
 * @param[in] word The word for which you are searching
 * @param[in] currWordIndex The index to word indicating which letter must
 *                          be matched by this call
 */
bool findWordHelper(const vector<vector<char> >& grid, 
		 Location currLoc,
		 Location delta,
		 string word,
		 unsigned int currWordIndex)
{
   /*** You complete ***/
   
   if(currWordIndex == word.size())
   {
   //know that the word is found once the currWordIndex has updated
   //such that it is now equal to the length of the word since
   //currWordIndex started at 1 and not 0, which means currWordIndex
   //is keeping track of each letter is goes through in the target word
   
      //cout << "Found the word!" << endl; 
      return true;
   }
   
   if(currLoc.row > grid.size()-1 || currLoc.col > grid[0].size()-1)
   {
   //setting the boundaries for the grid
   //rows and columns cannot go past the max values of the grid 
   //grid has rows 0-3 and columbs 0-4
   
      //cout << "Out of bounds" << endl;
      
      return false;
   }
   
   if(currLoc.row < 0 || currLoc.col < 0)
   {
   //setting the boundaries for the grid
   //rows and columns cannot start at negative values since the 
   //grid has rows 0-3 and columbs 0-4
   
      //cout << "Out of bounds" << endl;
      
      return false;
   }
   
   if(grid[currLoc.row][currLoc.col] == word[currWordIndex])
   {
   //check to see if the current letter grabbed in the grid 
   //is the next letter in the target word
   //if it is, modify the currLoc.row and currLoc.col by using the
   //information from Location delta
   //then recursively call findWordHelper to continue in the direction
   //determined in delta to eventually find the target letters of the word
      int row = currLoc.row + delta.row;
      int col = currLoc.col + delta.col;

      return findWordHelper(grid, Location(row, col), Location(delta.row, delta.col), word, currWordIndex+1);
   }
   
   else
   {
      return false;
   }

}

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide a grid filename and targetWord" << endl;
    return 1;
  }
  ifstream ifile(argv[1]);
  string targetWord(argv[2]);
  if(ifile.fail()){
    cerr << "Unable to open input grid file" << endl;
    return 1;
  }

  vector<vector<char> > mygrid;
  if( ! readGrid(ifile, mygrid) ){
    cerr << "Error reading grid" << endl;
    ifile.close();
    return 1;
  }

  findWord(mygrid, targetWord);

  return 0;
}
