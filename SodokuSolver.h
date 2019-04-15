//
// Created by takacchi on 09/04/19.
//

#ifndef SUDOKU_SOLVER_SODOKUSOLVER_H
#define SUDOKU_SOLVER_SODOKUSOLVER_H

#include "SodokuBoard.h"


class SodokuSolver
{
public:
    explicit SodokuSolver(std::string);
    explicit SodokuSolver(int[SIZE][SIZE]);
    explicit SodokuSolver(SodokuBoard);

    bool solve();
    std::string display_string();

private:
    bool find_solution(int);

private:
    SodokuBoard board;
};


#endif //SUDOKU_SOLVER_SODOKUSOLVER_H
