/*
Created By:- Rohan Kumar
Date: 19 June 2021

Implementation of backtracking algorithm and other game-play mechanics
*/

#include "solver.hpp"
#include <iostream>
#include <cassert>
#include <math.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to print the board
void Board::printPuzzle() {

    int blockSize = (int)sqrt(N);
    int extra_space = N / 10;

    for(int i = 0; i < N; i++){
        cout << "+---";
        for(int j = 0; j < extra_space; j++)
            cout << "-";
    }

    cout << "+" << endl;

    for(int i = 0; i < N; i++){
        cout << "| ";
        for(int j = 0; j < N; j++){

            if ((*this)(i,j) == 0){
                cout << ".";
                for(int k = 0; k < extra_space; k++)
                    cout << " ";
            } else {
                if (!isProblem(i,j)){
                    cout << (*this)(i,j);
                } else {
                    cout << "\033[31m" << (*this)(i,j) << "\033[39m";
                }

                int numDigits = (*this)(i,j)/10;
                while (numDigits < extra_space){
                    cout << " ";
                    numDigits++;
                }

            }

            if ((j+1) % blockSize == 0){
                cout << " | ";
            } else {
                cout << "   ";
            }
        }

        cout << endl;
        if ((i+1) % blockSize == 0){
            for(int j = 0; j < N; j++){
                cout << "+---";

                for(int k = 0; k < extra_space; k++)
                    cout << "-";
            }

            cout << "+" << endl;
        }

    }

}

// Check if the puzzle is complete
bool Board::checkPuzzle(){
    int val = 0;

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++){
            val = (*this)(i,j);
            (*this)(i,j) = 0;
            if(!feasible(*this, i, j, val)){
                (*this)(i,j) = val;
                return false;
            }
            (*this)(i,j) = val;
        }
    return true;
}

//Empty all cells that are not immutable
// immutable = prefilled by the randomly generated puzzle
void Board::clearPuzzle(){
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if (!checkImmutable(i,j))
                (*this)(i,j) = 0;
}

//Check if value is within size range of puzzle
//i.e. 1-9 on a 9x9 puzzle
bool Board::inBounds(int val){
    if ((val > 0) && (val <= N)){
        return true;
    } else {
        return false;
    }
}

//Checks for feasibility of the board
//Not useful to solvers because can't return as soon as problem exits
//Needs to cycle through whole board to update problem cells
//so that we can return red to the user....
bool Board::feasibleUser(int row, int col, int val){

    int blockSize =  (int)sqrt(N);

    if (row >= N){
        std::cout << "You can't play off the game board!" << endl;
        return false;
    }

    if (col >= N){
        std::cout << "You can't play off the game board!" << endl;
        return false;
    }

    bool isfeasible = true;

    for(int i = 0; i < N; i++){
        if((*this)(row,i) == val){
            infeasible[row][i] = true;
            isfeasible = false;
        } else {
            infeasible[row][i] = false;
        }
    }

    for(int i = 0; i < N; i++){
        if((*this)(i,col) == val){
            infeasible[i][col] = true;
            isfeasible = false;
        } else {
            infeasible[i][col] = false;
        }
    }

    int blockRow = blockSize*(row/blockSize);
    int blockCol = blockSize*(col/blockSize);

    // // See if used yet in block
    for(int i = 0; i < blockSize; i++){
        for(int j = 0; j < blockSize; j++){
            if((*this)(blockRow + i,blockCol + j) == val){
                infeasible[blockRow + i][blockCol + j] = true;
                isfeasible = false;
            } else {
                infeasible[blockRow + i][blockCol + j] = false;
            }
        }
    }
    return isfeasible;
}


// Helper function for solve: checks to see if candidate is feasible or not
bool feasible(Board &board, int row, int col, int val){
    int N = board.getSize();
    assert(row < N);
    assert(col < N);
    int blockSize = (int)sqrt(N);

    // See if used yet in row
    for(int j = 0; j < N; j++)
        if(board(row,j) == val) return false;

    // See if used yet in col
    for(int i = 0; i < N; i++)
        if(board(i,col) == val) return false;

    // coordinates of upper-left hand corner of block that (row,col) occupies
    int blockRow = blockSize*(row/blockSize);
    int blockCol = blockSize*(col/blockSize);

    // See if used yet in block
    for(int i = 0; i < blockSize; i++)
        for(int j = 0; j < blockSize; j++)
            if(board(blockRow + i,blockCol + j) == val)
                return false;

     return true;
}