#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <random>
#include "SodokuSolver.h"
#include "SodokuBoard.h"

using std::cout;
using std::cin;
using std::endl;

//void main_menu(SodokuBoard* = nullptr);
void main_menu(SodokuBoard&);
void play_menu(SodokuBoard&);
void take_coords(int&, int&);
//std::pair<int, int> take_coords();


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
                cout << "Filename to Load: ";
                cin >> filename;
                sodoku.load_board(filename);
                break;
            }
            case '4':
            {
                std::string filename;
                cout << "Filename to Deploy: ";
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

        char choice;
        cin >> choice;

        switch (choice)
        {
            case '1':
            {
                //std::pair<int, int> coords;
                int number, row, col;

                cout << "What number you want to set up? ";
                cin >> number;
                take_coords(row, col);

                sodoku.set_tile_value(row, col, number);
                break;
            }
            case '2':
            {
                //std::pair<int, int> coords;
                int row, col;

                cout << "What tile you want to wipe out?\n";
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

                cout << "For What tile you need help?\n";
                take_coords(row, col);

                cout << "What help you need?\n";
                cout << "1. Full 2. Column 3. Row 4. Box\n";
                cin >> answer;

                if (answer == '1') sodoku.possibilities(row, col);
                else if(answer == '2') sodoku.colmun_help(col);
                else if(answer == '4') sodoku.row_help(row);
                else if(answer == '3') sodoku.box_help(row, col);
                break;
            }
            case '5':
            {
                cout << "Check Correctness \n";
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
        cout << "Give Row <1 , 9>";
        cin >> row;
        cout << "Give Column <1 , 9>";
        cin >> col;
    } while (row < 1 || row > 9 || row < 1 || row > 9);

    row -= 1;
    col -= 1;
}