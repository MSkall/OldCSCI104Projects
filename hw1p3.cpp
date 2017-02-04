#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// *You* are not allowed to use global variables
//  but for just the output portion *we* will. ;>
int combo = 1;

// @brief Prints a single combination of teams
//
// @param[in] team1 Array containing the names of team 1
// @param[in] team2 Array containing the names of team 2
// @param[in] len Size of each array
void printSolution(const string* team1, const string* team2, int len)
{
  cout << "\nCombination " << combo++ << endl;
  cout << "T1: ";
  for(int i=0; i < len; i++){
    cout << team1[i] << " ";
  }
  cout << endl;
  cout << "T2: ";
  for(int i=0; i < len; i++){
    cout << team2[i] << " ";
  }
  cout << endl;
}

// You may add additional functions here




int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide a file of names" << endl;
    return 1;
  }
  // Complete the rest of main
 
  ifstream inFile("teams1.in");
  if(inFile.fail())
  {
  	cout << "Could not read file: " << "teams1.in" << endl;
  	return -1;
  }

  string p1, p2, p3, p4;
  int numPlayers;

  inFile >> numPlayers;
  cout << "Number of players: " << numPlayers << endl;
  //getline(inFile, line); //reads first line containig "4"


  inFile >> p1 >> p2 >> p3 >> p4;
  string team1[] = {p1, p2};
  string team2[] = {p3, p4};
  cout << p1 << p2 << p3 << p4<< endl;
  
  printSolution(team1, team2, 2);

  return 0;
}
