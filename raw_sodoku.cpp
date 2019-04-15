//
// Created by takacchi on 09/04/19.
//
#include <iostream>


#define DIM 9
#define BLANK 0
#define SPACE " "
#define LINE "|"
#define NEW_ROW "------------------------------------"
#define GRID_FULL std::make_pair(9, 9)

// Prints the Soduko grid
void print_grid(int grid[DIM][DIM])
{
    for (int row = 0; row < DIM; row++)
    {
        std::cout << SPACE << SPACE << SPACE << SPACE << SPACE << std::endl;
        std::cout << NEW_ROW << std::endl;

        for (int col = 0; col < DIM; col++)
        {
            std::cout << SPACE;
            if (BLANK == grid[row][col])
                std::cout << SPACE;
            else
                std::cout << grid[row][col];

            std::cout << SPACE << LINE;
        }
    }
    std::cout << std::endl << NEW_ROW << std::endl << std::endl;
}

// Return true if given number is in the specified row
bool used_in_row(int grid[DIM][DIM], int row, int num)
{
    for (int i = 0; i < DIM; i++)
    {
        if (grid[row][i] == num)
            return true;
    }

    return false;
}

// Return true if given number is in the specified column
bool used_in_column(int grid[DIM][DIM], int col, int num)
{
    for (int i = 0; i < DIM; i++)
    {
        if (grid[i][col] == num)
            return true;
    }

    return false;
}

// Return true if given number is in the box
bool used_in_box(int grid[DIM][DIM], int start_row, int start_col, int num)
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (grid[row + start_row][col + start_col] == num)
                return true;
        }
    }

    return false;
}

// Return true if it is legal to assign value to given location
bool is_legal(int grid[DIM][DIM], int row, int col, int num)
{
    return !used_in_row(grid, row, num) &&
           !used_in_column(grid, col, num) &&
           !used_in_box(grid, row - row % 3, col - col % 3 ,num);
}

// Search for location empty tile in grid
std::pair<int, int> get_unassigned_location(int grid[DIM][DIM])
{
    for (int row = 0; row < DIM; row++)
    {
        for (int col = 0; col < DIM; col++)
        {
            if (grid[row][col] == BLANK)
                return std::make_pair(row, col);
        }
    }

    return GRID_FULL;
}

// Takes a partially filled-in grid and attempts to assign values
// to all unassigned tiles
bool solve_soduko(int grid[DIM][DIM])
{
    // If grid has been filled
    if (GRID_FULL == get_unassigned_location(grid))
        return true;

    // Get an unassigned tile
    std::pair<int, int> tile_coord = get_unassigned_location(grid);
    int row = tile_coord.first;
    int col = tile_coord.second;

    for (int num = 1; num <= 9; num++)
    {
        // If assigning the current number in current
        // unassigned tile is legal
        if (is_legal(grid, row, col, num))
        {
            // assumption
            grid[row][col] = num;

            if (solve_soduko(grid))
                return true;

            // There is invalid number somewhere so we
            // are going back
            grid[row][col] = BLANK;
        }
    }

    // If we have gone through all possible numbers, then
    // we probably assigned a bad number early
    return false;
}