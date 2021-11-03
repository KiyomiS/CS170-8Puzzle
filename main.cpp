#include <iostream>
#include <string>
#include "Problem.h"
using namespace std;

int main() {
    int option, searchOption;
    int input;
    vector<int>start(9);
    cout << "Select your option:" << endl << " 1. Base Game\n 2. Create your own game" << endl;
    cin >> option;
    if(option == 1){
        cout << "Select search algorithm" << endl;
        cout << " Option 1: Uniform cost search\n Option 2: A* with the Misplaced Tile heuristic\n Option 3: A* with the Manhattan Distance heuristic" << endl;
        cin >> searchOption;
    }
    if(option == 2){
        cout << "Please enter your puzzle one integer at a time" << endl;
        for(int i = 0; i < 9; i++){//take in the puzzle one integer at a time
            cin >> input;
            start[i] = input;
        }
    }
//     puzzle base_puzzle = puzzle();
//     base_puzzle.PrintPuzzle();
//     puzzle new_puzzle = puzzle(start); //testing user inputs
//     new_puzzle.PrintPuzzle();

//testing each move
//     int i;
//     i = new_puzzle.GetZeroSpot();
//     cout << i << endl;

//     new_puzzle.MoveLeft(i);

//     new_puzzle.PrintPuzzle();

//     i = new_puzzle.GetZeroSpot();

//     new_puzzle.MoveRight(i);

//     new_puzzle.PrintPuzzle();
//     i = new_puzzle.GetZeroSpot();

//     new_puzzle.MoveUp(i);

//     new_puzzle.PrintPuzzle();
//     i = new_puzzle.GetZeroSpot();

//     new_puzzle.MoveDown(i);

//     new_puzzle.PrintPuzzle();
// }