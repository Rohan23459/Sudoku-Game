/*
Created By:- Rohan Kumar
Date: 16 June 2021
*/


#include <iostream>
#include <cstdlib>
#include<ctime>
#include "solver.hpp"
#include "altproj.hpp"
using namespace std;
using namespace arma;

int main(int argc, char **argv){
  
  srand(time(NULL));
  int n = 16;
  Board board = generatePuzzle(n,20);
  cout << "now!\n";
  //  board.printPuzzle();

  Board matt = DR(board);

  bool solve = matt.checkPuzzle();
  if(!solve)
    cout << "DR Failed to Solve" << endl;
  else
    matt.printPuzzle();

  //solve(board,0,0);
  //board.printPuzzle();
  
}

