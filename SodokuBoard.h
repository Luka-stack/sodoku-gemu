//
// Created by takacchi on 08/04/19.
//

#ifndef SUDOKU_SOLVER_SODOKUBOARD_H
#define SUDOKU_SOLVER_SODOKUBOARD_H

#include <string>
#include <vector>

#define SIZE 9
#define UNASSIGNED 0

class SodokuBoard
{
public:
    SodokuBoard()= default;
    explicit SodokuBoard(const int (*)[SIZE]);
    SodokuBoard(const SodokuBoard& sodoku) : SodokuBoard(sodoku.board) {}

    std::vector<int> get_tile_options(int, int);
    void box_remove_option(std::vector<int>&, int, int);
    void col_remove_option(std::vector<int>&, int);
    void row_remove_option(std::vector<int>&, int);

    void set_tile_value(int, int, int);
    void clear_tile_value(int, int);
    int  get_tile_value(int, int);

    void deploy_board(const std::string&);
    void load_board(const std::string&);
    void display_board();

    void get_random_board();
    bool find_solution(int=0);

private:

    int read_value(char);
    bool is_filled(int, int);
    static int get_difficulty_level();

private:
    int board[SIZE][SIZE]{};
};


#endif //SUDOKU_SOLVER_SODOKUBOARD_H
