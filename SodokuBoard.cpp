//
// Created by takacchi on 08/04/19.
//

#include <iostream>
#include <algorithm>
#include <fstream>
#include <random>
#include <chrono>
#include "SodokuBoard.h"

SodokuBoard::SodokuBoard(const int (*grid)[9] )
{
    std::copy(grid[0], grid[0]+SIZE*SIZE, &board[0][0]);
}

bool SodokuBoard::is_filled(int row, int col)
{
    return board[row][col] != 0;
}

std::vector<int> SodokuBoard::get_tile_options(int row, int col)
{
    std::vector<int> options = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    row_remove_option(options, row);
    col_remove_option(options, col);
    box_remove_option(options, row, col);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    std::shuffle(std::begin(options), std::end(options), e);

    return options;
}

void SodokuBoard::box_remove_option(std::vector<int> &options, int row_st, int col_st)
{
    int box_row = row_st - row_st% 3;
    int box_col = col_st - col_st% 3;

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            options.erase(std::remove(
                    options.begin(), options.end(), board[row + box_row][col + box_col]
                    ), options.end());
        }
    }
}

void SodokuBoard::col_remove_option(std::vector<int> &options, int col)
{
    for (auto & row : board)
        options.erase(std::remove(
                options.begin(), options.end(), row[col]
                ), options.end());
}

void SodokuBoard::row_remove_option(std::vector<int> &options, int row)
{
    for (int col = 0; col < SIZE; col++)
        options.erase(std::remove(
                options.begin(), options.end(), board[row][col]
                ), options.end());
}

void SodokuBoard::set_tile_value(int row, int col, int num)
{
    board[row][col] = num;
}

void SodokuBoard::clear_tile_value(int row, int col)
{
    board[row][col] = 0;
}

int SodokuBoard::get_tile_value(int row, int col)
{
    return board[row][col];
}

void SodokuBoard::load_board(const std::string& filename)
{
    std::ifstream in(filename + ".txt");

    char ch;
    for (auto & row : board)
    {
        for (auto& val : row)
        {
            in >> ch;
            val = read_value(ch);
        }
    }

    in.close();
    std::cout << "Sodoku was successfully loaded\n";
}

int SodokuBoard::read_value(char ch)
{
    return (ch != '.' ? ch - '0' : 0);
}

void SodokuBoard::deploy_board(const std::string& filename)
{
    std::ofstream out(filename + ".txt");

    for (auto & i : board)
    {
        for (int j : i)
        {
            //out << (j != 0 ? j : '.');
            if (j == 0)
                out << '.';
            else
                out << j;
        }
        out << '\n';
    }

    out.close();
    std::cout << "Sodoku was successfully deployed\n";
}

bool SodokuBoard::find_solution(int index)
{
    int row = index/SIZE;
    int col = index%SIZE;

    if (index == SIZE*SIZE)
        return true;

    if (is_filled(row, col))
        return find_solution(index+1);

    for (int value : get_tile_options(row, col))
    {
        set_tile_value(row, col, value);
        if (find_solution(index+1))
            return true;
    }

    clear_tile_value(row, col);
    return false;
}

void SodokuBoard::display_board()
{
    const std::string NEW_LINE = "-------+-----+-------+-----+-------";

    for (int row = 0; row < SIZE; row++)
    {

        if (row % 3 == 0)
            std::cout << std::endl;

        std::cout << '\t';


        for (int col = 0; col < SIZE; col++)
        {
            if (col == 3 || col == 6)
                std::cout << "  |  ";

            if (board[row][col] == UNASSIGNED)
                std::cout << " . ";
            else
                std::cout << " " << board[row][col] << " ";
        }

        if (row == 2 || row == 5)
            std::cout << "\n\t " << NEW_LINE;
        else
            std::cout << std::endl;
    }
}

void SodokuBoard::get_random_board()
{
    for (auto & i : board)
        for (int & j : i)
            j = UNASSIGNED;

    find_solution();
    int level = get_difficulty_level();

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6);

    std::vector<int> rand(81);
    std::iota (std::begin(rand), std::end(rand), 0);
    std::shuffle(std::begin(rand), std::end(rand), e);

    for (int i = 0; i < 81 - level; i++)
    {
        int row = rand.at(i) / SIZE;
        int col = rand.at(i) % SIZE;
        board[row][col] = UNASSIGNED;
    }

    std::cout << "\n\tSodoku has been successfully generated\n";
}

int SodokuBoard::get_difficulty_level()
{
    int level;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);

    do {
        std::cout << "\n\n\t Which Sodoku you want to solve?:\n";
        std::cout << "\t\t1.Easy\t2.Medium\t3.Hard\t4.Random\n";
        std::cout << "\t\t >>>";
        std::cin >> level;
    } while(level > 4 || level < 1);

    if (level == 1)
    {
        std::uniform_int_distribution<std::mt19937::result_type> dist6(36,41);
        return dist6(e);
    }
    else if (level == 2)
    {
        std::uniform_int_distribution<std::mt19937::result_type> dist6(31,36);
        return dist6(e);
    }
    else if (level == 3)
    {
        std::uniform_int_distribution<std::mt19937::result_type> dist6(25,30);
        return dist6(e);
    }
    else
    {
        std::uniform_int_distribution<std::mt19937::result_type> dist6(22,60);
        return dist6(e);
    }
}
