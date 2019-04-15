#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <random>
#include "SodokuSolver.h"
#include "SodokuBoard.h"

int main() {

    std::cout << "\t++++++++++++++++++++++++++++++++++++\n\n\t\t\t\tSoduko Solve\n\n";
    std::cout << "\t++++++++++++++++++++++++++++++++++++\n\n";

    SodokuBoard board;
    board.get_random_board();
    board.display_board();

    return 0;
}