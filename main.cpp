#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <random>
#include "SodokuBoard.h"

using std::cout;
using std::cin;
using std::endl;

//void main_menu(SodokuBoard* = nullptr);
void main_menu(SodokuBoard&);
void play_menu(SodokuBoard&);
void take_coords(int&, int&);
//std::pair<int, int> take_coords();
void print_possibilities(SodokuBoard&, int, int, int=1);
void check_all_dimensions(SodokuBoard&);



int main()
{
    SodokuBoard board;
    main_menu(board);

    return 0;
}

void main_menu(SodokuBoard& sodoku)
{
    cout << endl << endl;
    cout << "\t\t@---->>>>> \t\t Welcome \t <<<<<----@" << endl;
    cout << "\t\t@---->>>>>  It's Sodoku Game <<<<<----@" << endl;

    while(true) {
        cout << "\n\t\t\t What you want to do?\n";
        cout << "\t\t\t 1. Play" << endl;
        cout << "\t\t\t 2. Generate Random Sodoku" << endl;
        cout << "\t\t\t 3. Load Sodoku from File" << endl;
        cout << "\t\t\t 4. Deploy Sodoku to File" << endl;
        cout << "\t\t\t 5. Exit" << endl;
        cout << "\t\t\t >>> ";

        char choice;
        cin >> choice;

        switch (choice) {
            case '1':
                play_menu(sodoku);
                break;

            case '2':
                sodoku.get_random_board();
                break;

            case '3':
            {
                std::string filename;
                cout << "\t\t\tFilename to Load:\n";
                cout << "\t\t\t >>>";
                cin >> filename;
                sodoku.load_board(filename);
                break;
            }
            case '4':
            {
                std::string filename;
                cout << "\t\t\tFilename to Deploy:\n";
                cout << "\t\t\t >>>";
                cin >> filename;
                sodoku.deploy_board(filename);
                break;
            }
            case '5':
                cout << "\n\t\t\t Good Bye! :-)";
                exit(0);

            default:
                cout << "\n\t\t\t WARNING! WRONG INPUT!";
                main_menu(sodoku);
        }
    }
}

void play_menu(SodokuBoard& sodoku)
{
    cout << endl << endl;
    cout << "\t\t@---->>>>>  Your Board <<<<<----@" << endl;

    while(true) {
        sodoku.display_board();

        cout << "\n\t\t\t What you want to do?\n";
        cout << "\t\t\t 1. Put Number At Tile" << endl;
        cout << "\t\t\t 2. Clear Tile" << endl;
        cout << "\t\t\t 3. Solve Sodoku" << endl;
        cout << "\t\t\t 4. Get Help" << endl;
        cout << "\t\t\t 5. Check Correctness" << endl;
        cout << "\t\t\t 6. Back To Main Menu" << endl;
        cout << "\t\t\t >>> ";

        char choice;
        cin >> choice;

        switch (choice)
        {
            case '1':
            {
                //std::pair<int, int> coords;
                int number, row, col;

                cout << "\n\t\t\tWhat number you want to set up?\n";
                cout << "\t\t\t >>> ";
                cin >> number;
                take_coords(row, col);

                sodoku.set_tile_value(row, col, number);
                break;
            }
            case '2':
            {
                //std::pair<int, int> coords;
                int row, col;

                cout << "\n\t\t\tWhat tile you want to wipe out?\n";
                take_coords(row, col);

                sodoku.clear_tile_value(row, col);
                break;
            }
            case '3':
            {
                sodoku.find_solution();
                break;
            }
            case '4':
            {
                int row, col;
                char answer;

                cout << "\n\t\t\tFor What tile you need help?\n";
                take_coords(row, col);

                cout << "\n\t\t\tWhat help you need?\n";
                cout << "\t\t\t1. Full 2. Column 3. Row 4. Box\n";
                cout << "\t\t\t >>> ";
                cin >> answer;

                if (answer == '1') print_possibilities(sodoku, row, col);
                else if(answer == '2') print_possibilities(sodoku, row, col, 2);
                else if(answer == '3') print_possibilities(sodoku, row, col, 3);
                else if(answer == '4') print_possibilities(sodoku, row, col, 4);
                else cout << "\n\t\t\t WRONG INPUT!\n";
                break;
            }
            case '5':
            {
                char answer;

                cout << "\n\t\t\tWhat Check you need?\n";
                cout << "\t\t\t1. Solvable 2. Check Tile\n";
                cout << "\t\t\t >>> ";
                cin >> answer;

                if (answer == '1')
                {
                    if (sodoku.find_solution())
                    {
                        cout << "\n\t\t\tThere're no Errors in your Sodoku\n";
                    }
                    else
                    {
                        cout << "\n\t\t\tAttention. Your Sodoku has Errors!\n";
                    }
                }
                else if(answer == '2') check_all_dimensions(sodoku);
                else cout << "\n\t\t\t WRONG INPUT!\n";
                break;
            }
            case '6':
                main_menu(sodoku);
                break;

            default:
                cout << "\n\t\t\t WARNING! WRONG INPUT!";
                play_menu(sodoku);
        }
    }
}

/*std::pair<int, int> take_coords()
{
    int col, row;

    do {
        cout << "Give Column <1 , 9>";
        cin >> col;
        cout << "Give Column <1 , 9>";
        cin >> row;
    } while (col < 1 || col > 9 || row < 1 || row > 9);

    return std::pair<int, int>(col-1, row-1);
}*/

void take_coords(int& row, int& col)
{
    do {
        cout << "\t\t\tGive Row <1 , 9>\n";
        cout << "\t\t\t >>>";
        cin >> row;
        cout << "\t\t\tGive Column <1 , 9>\n";
        cout << "\t\t\t >>>";
        cin >> col;
    } while (row < 1 || row > 9 || row < 1 || row > 9);

    row -= 1;
    col -= 1;
}

void print_possibilities(SodokuBoard& board, int row , int col, int ans)
{
    std::vector<int> options = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    if (ans == 1)
    {
        board.row_remove_option(options, row);
        board.col_remove_option(options, col);
        board.box_remove_option(options, row, col);
    }
    else if (ans == 2)
        board.col_remove_option(options, col);
    else if (ans == 3)
        board.row_remove_option(options, row);
    else if (ans == 4)
        board.box_remove_option(options, row, col);

    cout << "\n\t\t\t Your Possibilities Are < ";
    for (int pos : options)
        cout << pos << " ";
    cout << " >" << endl;
}

void check_all_dimensions(SodokuBoard& board)
{
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            int valueAt = board.get_tile_value(row, col);
            if (valueAt == 0)
                continue;

            board.set_tile_value(row, col, 0);
            std::vector<int> options = board.get_tile_options(row, col);
            board.set_tile_value(row, col, valueAt);

            if(!(std::find(options.begin(), options.end(), valueAt) != options.end())) {
                // does not contain x
                cout << "\n\t\t\tThere is Error. Row: " << row+1 << " Col: " << col+1 << endl;
                return;
            }

        }
    }

}
