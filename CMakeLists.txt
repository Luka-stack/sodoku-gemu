cmake_minimum_required(VERSION 3.13)
project(sudoku_solver)

set(CMAKE_CXX_STANDARD 17)

add_executable(sudoku_solver main.cpp SodokuBoard.cpp SodokuBoard.h SodokuSolver.cpp SodokuSolver.h raw_sodoku.cpp)