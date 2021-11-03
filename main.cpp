#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "problem.h"
#include "Node.h"

using namespace std;

Node * uniformSearch(problem * prb, vector<int> start_point);

int main() {
    int option, searchOption;
    int input;
    vector<int>start = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    cout << "Select your option:" << endl << " 1. Base Game\n 2. Create your own game" << endl;
    cin >> option;
    if(option == 2){
        cout << "Please enter your puzzle one integer at a time with spaces" << endl;
        for(int i = 0; i < 9; i++){//take in the puzzle one integer at a time
            cin >> input;
            start[i] = input;
        }
    }
    cout << "Select search algorithm" << endl;
    cout << " Option 1: Uniform cost search\n Option 2: A* with the Misplaced Tile heuristic\n Option 3: A* with the Manhattan Distance heuristic" << endl;
    cin >> searchOption;

    problem * start_game = new problem(start);
    Node * game_over = nullptr;
    Node* print_start = new Node(start_game->getState());

    print_start->PrintState();

    //Node * check = start_game->Child(print_start, 4); checking moving functions in nodes
    //check->PrintState();

    // if(searchOption == 1){
    //     game_over = uniformSearch(start_game, start);
    // }

    // game_over->PrintState();
//     puzzle base_puzzle = puzzle();
//     base_puzzle.PrintPuzzle();
//     puzzle new_puzzle = puzzle(start); //testing user inputs
//     new_puzzle.PrintPuzzle();

//testing each move as operators first.
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
}

Node * uniformSearch(problem * prb, vector<int> start_point){
    unsigned long long numberofNodes = 0;
    unsigned long long depth = 0;
    priority_queue<Node*> uniform_queue;
    Node* begin = new Node(start_point);
    vector<Node*> track;
    uniform_queue.push(begin);

    while(!uniform_queue.empty()){
        Node * check = uniform_queue.top(); //taking the first node, at the beginning it will be the node passed in or default node
        track.push_back(check);
        uniform_queue.pop(); //remove node we are checking because we wont have to check it again since we're creating all of its children.
        if (check->getState() == prb->getGoal()){ //checking if we're at the goal state
            cout << "Puzzle Solved." << endl << "The cost was: " << numberofNodes << endl;
            return check;
        }
        //not in goal state, check to expand nodes.
        depth++; // keep track of depth
        for(int i = 0; i < 4; i++){ //have to check 4 operators
            numberofNodes++; //keep track of number of nodes created
            if(prb->canDo(check, i)){ //if it is a valid move
                Node* createChild = prb->Child(check, i); //create the child node
                uniform_queue.push(createChild); //adding new children to queue
                cout << "Pushing" << endl;
                createChild->PrintState();
            }
        }
    }
    return nullptr;
}