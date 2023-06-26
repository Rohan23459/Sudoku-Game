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
