#ifndef PUZZLE_H
#define PUZZLE_H
#include <iostream>
#include <vector>
using namespace std;

class puzzle {
    private:
       vector<int>puzzle_state = {1, 2, 3, 4, 5, 6, 7, 8, 0}; // array of size 9 to hold the puzzle.
       int cost;
       puzzle * previous;
    public:
        puzzle() {
            cost = 0;
            previous = NULL;
        };

        puzzle(vector<int> input_puzzle){
            this->puzzle_state = input_puzzle;
        };

        void PrintPuzzle(){ //outputs the vector
            for(int i = 0; i < 9; i++){
                cout << puzzle_state[i] << " ";
                if(i == 2 || i == 5 || i == 8){
                    cout << endl;
                }
            }
        }

        void MoveLeft(vector<int> input_puzzle, int zero_spot){
            input_puzzle[zero_spot] = input_puzzle[zero_spot - 1];
            input_puzzle[zero_spot] = 0;
        }

        void MoveRight(vector<int> input_puzzle, int zero_spot){
            input_puzzle[zero_spot] = input_puzzle[zero_spot + 1];
            input_puzzle[zero_spot] = 0;
        }

        void MoveUp(vector<int> input_puzzle, int zero_spot) {
            input_puzzle[zero_spot] = input_puzzle[zero_spot - 3];
            input_puzzle[zero_spot] = 0;
        }

        void MoveDown(vector<int> input_puzzle, int zero_spot) {
            input_puzzle[zero_spot] = input_puzzle[zero_spot + 3];
            input_puzzle[zero_spot] = 0;
        }
};

class row : puzzle {

};

// 1 2 3 
// 4 5 6
// 7 8 0
// 1 2 3 4 5 6 7 8 9
// up = - 3 indices, down = + 3, left = + 1, right = - 1 
//include edge cases for each.
#endif