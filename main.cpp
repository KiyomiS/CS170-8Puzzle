#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "problem.h"
#include "Node.h"
#include "custom_priority_queue.h"

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

    if(searchOption == 1){
        game_over = uniformSearch(start_game, start);
    }

    game_over->PrintState();
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
    custom_priority_queue<Node*> uniform_queue;
    Node* begin = new Node(start_point);
    vector<Node*> track; //keep track of all states
    vector<Node*> expandedSet; //keep track of all states that have already been expanded.
    uniform_queue.push(begin);
   
    while(!uniform_queue.empty()){
        Node * check = uniform_queue.top(); //taking the first node, at the beginning it will be the node passed in or default node
        
        if(track.empty()){
            track.push_back(check); // keep track of all different visited states so if we run into the same state we can compare costs.
        }

        uniform_queue.pop(); //remove node we are checking because we wont have to check it again since we're creating all of its children.
        if (check->getState() == prb->getGoal()){ //checking if we're at the goal state
            cout << "Puzzle Solved." << endl << "The cost was: " << check->getCost() << endl;
            return check;
        }
        //not in goal state, check to expand nodes.
        depth++; // keep track of depth
        expandedSet.push_back(check);
        for(int i = 0; i < 4; i++){ //have to check 4 operators
            numberofNodes++; //keep track of number of nodes created
            if(prb->canDo(check, i)){ //if it is a valid move
                Node* createChild = prb->Child(check, i); //create the child node

                bool istrue = false;
                for(int i = 0; i < expandedSet.size(); i++){ //looking to see state has already been visited
                    // cout << "Checking" << endl;
                    cout << "checking if state has been visited" << endl;
                    if(expandedSet[i]->getState() == createChild->getState()){ //if state is visited
                         istrue = true;
                    }
                }
                cout << "done checking" << endl;
                if(!istrue) { //not an old expanded state, check if its in queue
                    if(!uniform_queue.find(createChild)){ //if its not in the queue nor has it been expanded
                        uniform_queue.push(createChild); //add to queue
                        track.push_back(createChild); //add to track as well
                        cout << "option" << endl;
                        createChild->PrintState();
                    } else { // its in the queue but not expanded yet.
                        for(int i = 0; i < track.size(); i++) {
                            if(track[i]->getState() == createChild->getState()){ //find the one in the queue by looking through track
                                if(track[i]->getCost() < createChild->getCost()){ //check if node in track has less cost
                                    uniform_queue.push(track[i]); //if so add it instead of new child
                                    //delete createChild;
                                    cout << "Option" << endl;
                                    track[i]->PrintState();
                                } else {
                                    uniform_queue.remove(createChild);
                                    uniform_queue.push(createChild); //add new lower node
                                    track[i]->setCost(createChild->getCost()); //set the tracked nodes cost to lower of the two.
                                    cout << "Option" << endl;
                                    createChild->PrintState(); 
                                }
                            }
                        } 
                    }
                }                 
            }
        }
    }
    return nullptr;
}
