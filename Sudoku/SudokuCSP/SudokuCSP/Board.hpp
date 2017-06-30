//
//  Board.hpp
//  SudokuCSP
//  Header file for the Board.cpp class
//  Here is where we have our methods for the Board class and declare the gameBoard 2D vector
//
//  Created by Kendall Weistroffer on 10/2/16.
//  Copyright © 2016 Kendall Weistroffer. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>
#include <vector>


class Board{
 
public:
    Board();
    bool iterateSolved(int &row, int &col);
    bool inRow(int row, int val);
    bool inCol(int col, int val);
    bool inBlock(int newX, int newY, int val);
    bool isLegal(int row, int col, int val);
    bool sudokuSolver();
    void print();
    
    
private:
    std::vector<std::vector<int>>gameBoard;

};

#endif /* Board_hpp */
