//
//  Board.cpp
//  SudokuCSP
//  Here is where we do the Sudoku solving. The gameBoard 2D vector is initilaized to be whatever
//  9x9 Sudoku problem we are solving. The solver works by implemenging DFS and constraints that
//  align with the rules of Sudoku to ensure that we are making valid moves.

//  Created by Kendall Weistroffer on 10/2/16.
//  Copyright © 2016 Kendall Weistroffer. All rights reserved.
//

#include "Board.hpp"
#include <iostream>

/*
 Here is our class constructor. In here we initilize the gameBoard variable to our
 selected 9x9 sudoku problem. 0's represent the blank spaces within the Sudoku problem. 
 */
Board::Board(){
    
    gameBoard = /* { {0,0,0,7,4,0,0,0,0},
                 {3,0,0,0,0,0,1,6,0},
                 {4,0,0,1,0,0,0,7,0},
                 {0,0,0,8,9,0,0,0,1},
                 {9,0,0,5,0,7,0,0,8},
                 {6,0,0,0,1,3,0,0,0},
                 {2,7,0,0,0,5,4,0,3},
                 {0,3,6,0,0,0,0,0,5},
                 {0,0,0,0,7,1,0,8,6}}; */
    
                /*  {{0,7,6,0,0,0,9,4,3},
                    {4,0,2,0,0,0,0,6,5},
                    {9,0,3,6,1,0,0,7,0},
                    {7,0,0,0,0,6,8,0,0},
                    {0,0,0,7,2,0,0,0,0},
                    {0,0,0,5,9,0,0,3,0},
                    {5,2,0,3,0,0,0,0,0},
                    {0,3,1,2,0,0,0,5,0},
                    {8,0,7,0,4,0,0,0,0}}; */
    
                  /*  { {0,0,0,2,0,0,0,6,3},
                    {3,0,0,0,0,5,4,0,1},
                    {0,0,1,0,0,3,9,8,0},
                    {0,0,0,0,0,0,0,9,0},
                    {0,0,0,5,3,8,0,0,0},
                    {0,3,0,0,0,0,0,0,0},
                    {0,2,6,3,0,0,5,0,0},
                    {5,0,3,7,0,0,0,0,8},
                    {4,7,0,0,0,1,0,0,0}};*/
    
    
   { {0,8,1,0,0,0,6,2,0},
     {0,9,0,4,0,6,0,7,0},
     {5,0,0,0,0,0,0,0,8},
     {3,0,0,0,0,0,0,0,1},
     {0,0,0,7,0,2,0,0,0},
     {0,6,8,0,0,0,3,9,0},
     {0,0,0,6,0,9,0,0,0},
     {0,3,0,0,0,0,0,5,0},
     {0,0,0,0,5,0,0,0,0}};
    
}

/*
 Here we iterate through the game board looking for unfilled cells.
 If we hit a unfilled cell (ie a zero) then we know that the gameboard
 is not complete and therefore we have not found a solution. 
 */

bool Board::iterateSolved(int &row, int &col){
    
    for(row = 0; row <= 8; row++){
        for(col = 0;col <= 8; col++){
            if(gameBoard[row][col] == 0){
                return false;
            }
        }
    }
    return true;
}


/* 
 Here we check to make sure that the value that we are at is not already
 present in the same row.
 */

bool Board::inRow(int row, int val){
    for(int i = 0; i<= 8; i++){
        if(gameBoard[row][i] == val){
            return true;
        }
    }
    return false;
    
}
/*
 Here we check to make sure that the value that we are at is not already
 present in the same column.
 */
bool Board::inCol(int col, int val){
    for(int i = 0; i<= 8; i++){
        if(gameBoard[i][col] == val){
            return true;
        }
    }
    return false;
}

/*
 Here we check to make sure that the value that we are at is not already
 present in the same 3x3 block.
 */
bool Board::inBlock(int newX, int newY, int val){
    for(int i = 0; i<=2;i++){
        for(int j = 0; j<=2; j++){
            
            if(gameBoard[newX+i][newY+j] == val){
                return true;
            }
        }
    }
    return false;
}
/*
 Here apply the previous three methods to ensure that the value we are about
 to insert into our gameBoard is legal (so it doesn't already exist in the same
 row/column/block)
 */
bool Board::isLegal(int row, int col, int val){
    return !inRow(row, val) && !inCol(col, val) && !inBlock(row-row%3,col-col%3,val);
}
/*
 Where the solving of the sudoku takes place using DFS (Backtracking)
 */
bool Board::sudokuSolver(){
    int row;
    int col;
    
    //iterate through, looking for blanks (and if we are done or not)
    if(iterateSolved(row, col)){
        return true;
    }
    //iterate through all the possible values
    for(int k = 1; k <= 9; k++){
        
        //if we are at a blank and the value we're currently at is a legal move
        //then update the gameBoard with the new value and recursively move on
        //to begin the process again.
        if(gameBoard[row][col] == 0 && isLegal(row,col,k)){
            gameBoard[row][col] = k;
            
            if(sudokuSolver()){
                return true;
            }
            //Reset gameBoard
            gameBoard[row][col] = 0;
        }
        
    }
    
    return false;
}


//print out the Sudoku board
void Board::print(){
    
    for(int i=0; i <=8; i++){
        for(int j = 0; j <= 8; j++){
            std::cout << gameBoard[i][j] << " ";
            
        }
        std::cout << std::endl;
    }
}

