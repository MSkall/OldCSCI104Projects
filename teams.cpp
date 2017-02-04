/* Marlena Skall
   1/24/17
   CSCI 104
   Problem #6
   Teams
*/

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
void printSolution(const string* team1, 
		   const string* team2,
		   int len)
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

void findTeams(string* list_names, string* T1, string* T2, int numPlayers, 
               int sizeTeam1, int sizeTeam2, int index);

int main(int argc, char* argv[])
{
   if(argc < 2){
      cerr << "Please provide a file of names" << endl;
      return 1;
   }
   // Complete the rest of main

   ifstream myfile(argv[1]);
   if(myfile.fail())
   {
      cout << "Error" << endl;
      return 1;
   }
   
   int players;
   myfile >> players; //read in the total numbers of players
                      //that will be used to make teams
   
   string playerName;
   int playerIndex = 0; //start counter to keep track of players at 0
   int sizeT1 = 0; //teams not yet filled 
   int sizeT2 = 0; //so set size of both to 0
   
   string* list_names = new string[players];
   string* T1 = new string[players/2]; //teams need to be divided up
   string* T2 = new string[players/2]; //so equal number of players
   
   for(int i = 0; i < players; i++)
   {
      myfile >> playerName;
      list_names[i] = playerName;
   }
   
   //call findTeams to fill in team combinations
   findTeams(list_names, T1, T2, players, sizeT1, sizeT2, playerIndex);
   
   //deallcoate memory
   delete[] T1;
   delete[] T2;
   delete[] list_names;
   

   return 0;
}

void findTeams(string* list_names, string* T1, string* T2, 
               int numPlayers, int sizeTeam1, int sizeTeam2, int index)
{
   //base case 
   if( (sizeTeam1 + sizeTeam2) == numPlayers )
   {
      //if teams are full, then print out the solution of the teams combos
      printSolution(T1, T2, (numPlayers/2));
   }
   
   //recursive case
   else
   {
      //if the size of team1 is not yet full, add player to team1
      if(sizeTeam1 < numPlayers/2)
      {
         T1[sizeTeam1] = list_names[index];
         findTeams(list_names, T1, T2, numPlayers,
            sizeTeam1+1, sizeTeam2, index+1);
      }
      
      //if the size of team2 is not yet full, add player to team2
      if(sizeTeam2 < numPlayers/2)
      {
         T2[sizeTeam2] = list_names[index];
         findTeams(list_names, T1, T2, numPlayers, 
            sizeTeam1, sizeTeam2+1, index+1);
      
      }
   
   }

} 
