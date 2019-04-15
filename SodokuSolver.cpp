//
// Created by takacchi on 09/04/19.
//
/*
#include "SodokuSolver.h"

SodokuSolver::SodokuSolver(std::string sodoku)
{
    board.read_board(sodoku);
}

SodokuSolver::SodokuSolver(SodokuBoard board)
{
    this->board = board;
}

SodokuSolver::SodokuSolver(int grid[SIZE][SIZE])
{
    board.copy_board(grid);
}

bool SodokuSolver::solve()
{
    return find_solution(0);
}

bool SodokuSolver::find_solution(int index)
{
    int row = index/SIZE;
    int col = index%SIZE;

    if (index == SIZE*SIZE)
        return true;

    if (board.is_filled(row, col))
        return find_solution(index+1);

    for (int value : board.get_tile_options(row, col))
    {
        board.set_tile_value(row, col, value);
        if (find_solution(index+1))
            return true;
    }

    board.clear_tile_value(row, col);
    return false;
}

std::string SodokuSolver::display_string()
{
    return board.dump_board();
}*/


