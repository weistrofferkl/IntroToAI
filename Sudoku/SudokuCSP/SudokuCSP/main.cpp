//
//  main.cpp
//  SudokuCSP
//
//  Created by Kendall Weistroffer on 10/2/16.
//  Copyright © 2016 Kendall Weistroffer. All rights reserved.
//

#include <iostream>
#include "Board.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    //std::cout << "Hello, World!\n";
    
    Board myBoard;
   
    if(myBoard.sudokuSolver()){
        myBoard.print();
        std::cout << "Found something" << std::endl;
    }
    else{
        std::cout << "No solution" << std::endl;
    }
    
    return 0;
}
